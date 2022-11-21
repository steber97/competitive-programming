
import argparse
import math

args = argparse.ArgumentParser()
args.add_argument("--files", type=str, nargs='+', help="files to parse, should be one", required=True)
args.add_argument("--commit_msg", type=str, help='commit message', required=True)

args_main = args.parse_args()

# The path of the readme is absolute, because this script is always 
# invoked by the root folder competitive-programming/ by the commit-msg git hook
README_PATH = "uva/README.md"
CHAPTER_IDENTIFIER = "## Chapter "

def handle_uva_readme(filename: str, commit_msg: str):
    """
    All paths are wrt competitive-programming/ root folder.
    Given a file added with the last commit and a commit message, update the README
    such that it includes the new file.
    The new file is added in the correct position in the README, namely under the correct 
    chapter and in the correct order (by problem number).
    The README file is overridden with the new line describing the newly committed file.
    This script is invoked by the msg-commit hook in .git/hooks.
    In the README file, chapters should start with `## Chapter x: title of the chapter`

    @param filename: string with path to file added. 
        Should be the main solver under a folder in `uva/chapter_x_.../problemnumber/main.*`
    @param commit_msg: commit message of the form `Add UVa problemnumber problemname somedescription"
    """
    if 'chapter_' not in filename:
        print("Chapter not specified as `chapter_` in the filename {}".format(filename))
        return
    
    try:
        # Chapter number is taken from the folder.
        chapter = int(filename.split("chapter_")[1].split("_")[0])
        # Problem number is taken from the folder.
        number = int(filename.split("chapter_")[1].split("/")[1].split("/")[0])
    except ValueError:
        print("filename {} is not of the format".format(filename) +
        " `uva/chapter_x_somedescription/problemnumber/filename.*`")
        return
    
    lines_in = []
    with open(README_PATH) as f:
        for l in f:
            lines_in.append(l)
    
    # Get where chapter starts and where it ends (line number).
    chapter_intervals = []
    for i in range(len(lines_in)):
        if lines_in[i][:len(CHAPTER_IDENTIFIER)] == CHAPTER_IDENTIFIER:
            if len(chapter_intervals) == 0:
                chapter_intervals.append([i+1, i+1])
            else:
                chapter_intervals[-1][1] = i
                chapter_intervals.append([i+1,i+1])
    if len(chapter_intervals) > 0:
        chapter_intervals[-1][1] = len(lines_in)
    
    print(chapter_intervals)
    print(chapter)

    pos = -1
    chapter_name = ""
    if chapter <= len(chapter_intervals):
        for i in range(chapter_intervals[chapter-1][0], chapter_intervals[chapter-1][1]-1):
            # Every line is formatted as `- [probnumber](url) name description`
            if '- [' in lines_in[i]:
                num1 = int(lines_in[i].split("- [")[1].split("]")[0])
                chapter_name = "chapter_" + l.split('chapter_')[1].split("/")[0]
            else:
                num1 = -1
            
            if '- [' in lines_in[i+1]:
                num2 = int(lines_in[i+1].split("- [")[1].split("]")[0])
            else:
                num2 = -1
            
            if num1 != -1 and num2 != -1:
                if number < num1 and number < num2:
                    # Special case, number to insert is the first.
                    pos = i
                    break
                if num1 < number and number < num2:
                    pos = i+1
                    break
        if pos == -1:
            # Special case, the number to insert is the last.
            pos = chapter_intervals[chapter-1][1]
    else:
        print("There are not enough chapters in {}. ".format(README_PATH) +
              "New added file is in chapter {} ".format(chapter) + 
              "But found only {} chapters in the README file".format(len(chapter_intervals)))
        
    if pos != -1 and chapter_name != '':
        if pos == len(lines_in):
            # Add newline char if we insert the line at the last position.
            lines_in[-1] = lines_in[-1] if lines_in[-1][-1] == '\n' else lines_in[-1] + '\n'
        newline = "- [{}]({}{}/{}) {}\n".format(
            number, 
            "https://github.com/steber97/competitive-programming/tree/main/uva/",
            chapter_name,
            number,
            commit_msg.split("Add UVa {} ".format(number))[1]
        )
        lines_in.insert(pos, newline)
        print("New line added to README.md")
        print(newline)
    
        with open(README_PATH, 'w') as f:
            f.writelines(lines_in)
    else:
        print("Could not insert the problem in the README.")
        return


"""
    This python script updates the README.md in uva/ folder.
    It simply adds a line in the README.md with the new problem solved, using the format
    -[problem number](github url) Name of Problem (Some description about how it was solved)
    It expects to receive only one file as argument (under the uva folder)
    The message should be of the format `Add UVa problemnumber Some description`. 
    The problem number must be coherent 
    (namely, the folder of the file added and the problem number in the commit message must coincide).
    The chapter subsection must be already present in the README.
"""
if __name__=="__main__":

    files = args_main.files
    commit_msg = args_main.commit_msg

    if len(files) == 1:
        if "Add UVa" in commit_msg:
            if 'uva/' in files[0]:
                handle_uva_readme(files[0], commit_msg)
            else:
                print("path {} misses `uva/` folder".format(files[0]))
        else:
            print(
                "Missing `Add UVa` in commit message `{}`, cannot be UVa format."
                .format(commit_msg))
    else:
        print(">1 files added ({}), cannot be UVa format.".format(len(files)))