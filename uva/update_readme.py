
import argparse
import math

args = argparse.ArgumentParser()
args.add_argument("--files", type=str, nargs='+', help="files to parse, should be one", required=True)
args.add_argument("--msg", type=str, help='commit message', required=True)

args_main = args.parse_args()


def handle_uva_readme(filename: str, msg: str):
    chapter = int(filename.split("chapter_")[1].split("_")[0])
    number = int(filename.split("chapter_")[1].split("/")[1].split("/")[0])
    
    lines_in = []
    lines_out = []
    with open("README.md") as f:
        for l in f:
            lines_in.append(l)
    
    chapter_intervals = []
    for i in range(len(lines_in)):
        if "## Chapter " in lines_in[i]:
            if len(chapter_intervals) == 0:
                chapter_intervals.append([i+1, i+1])
            else:
                chapter_intervals[-1][1] = i
                chapter_intervals.append([i+1,i+1])
    if len(chapter_intervals) > 0:
        chapter_intervals[-1][1] = len(lines_in)
    
    pos = -1
    chapter_name = ""
    if chapter <= len(chapter_intervals):
        for i in range(chapter_intervals[chapter-1][0], chapter_intervals[chapter-1][1]-1):
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
                    # Special case, number is the first.
                    pos = i
                    break
                if num1 < number and number < num2:
                    pos = i+1
                    break
        if pos == -1:
            pos = chapter_intervals[chapter-1][1]
        
    if pos != -1:
        if pos == len(lines_in):
            lines_in[-1] = lines_in[-1] if lines_in[-1][-1] == '\n' else lines_in[-1] + '\n'
        newline = "- [{}]({}{}/{}) {}\n".format(
            number, 
            "https://github.com/steber97/competitive-programming/tree/main/uva/",
            chapter_name,
            number,
            msg.split("Add UVa {} ".format(number))[1]
        )
        lines_in.insert(pos, newline)
        print("New line added to README.md")
        print(newline)
    
    with open("README.md", 'w') as f:
        f.writelines(lines_in)

if __name__=="__main__":
    files = args_main.files
    msg = args_main.msg

    if len(files) == 1:
        if "Add UVa" in msg:
            if 'uva/' in files[0]:
                handle_uva_readme(files[0], msg)