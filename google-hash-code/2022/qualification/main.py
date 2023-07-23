import pandas as pd
import numpy as np
from typing import List
from binary_tree.tree import BinaryTree, Node


class Project:
    def __init__(self, name: str, days: int, score: int, best_before: int, roles_names: List[str], roles_level: List[int]):
        self.name = name
        self.days = days
        self.score = score
        self.best_before = best_before
        self.roles_names = roles_names
        self.roles_levels = roles_level
    def __repr__(self) -> str:
        return "{}".format(self.name)


class Contributor:
    def __init__(self, name: str, skills: object):
        self.name = name
        # Map skill_name -> skill_level
        self.skills = skills


def get_input():
    C, P = input().split(" ")
    C, P = int(C), int(P)
    contributors = []
    for i in range(C):
        name, skills_n = input().split(" ")
        skills_n = int(skills_n)
        skills = {}
        for s in range(skills_n):
            skill, level = input().split(" ")
            level = int(level)
            skills[skill] = level
        contributors.append(Contributor(name, skills))
    projects = []
    for p in range(P):
        name, days, score, best_before, roles_n = input().split(" ")
        roles_n = int(roles_n)
        best_before = int(best_before)
        score = int(score)
        days = int(days)
        roles_names = []
        roles_level = []
        for r in range(roles_n):
            role_name, skill_level = input().split(" ")
            skill_level = int(skill_level)
            roles_names.append(role_name)
            roles_level.append(skill_level)
        projects.append(Project(name, days, score, best_before, roles_names, roles_level))

    return contributors, projects


class JobAssignment:
    def __init__(self, project, contributors, start_day) -> None:
        self.project = project
        self.contributors = contributors
        self.start_day = start_day
    
    def __repr__(self) -> str:
        return "{}\n{}".format(self.project.name, " ".join([c.contributor.name for c in self.contributors]))


class InterestingDay:
    def __init__(self, day, jobs_finishing: List[JobAssignment]) -> None:
        self.day = day
        self.jobs_finishing = jobs_finishing
    
    def __lt__(self, other):
        return self.day < other.day
    
    def __gt__(self, other):
        return self.day > other.day
    
    def __ge__(self, other):
        return self.day >= other.day

class ContributorSkillLevel:
    def __init__(self, contributor, skill, level):
        self.contributor = contributor
        self.skill = skill
        self.level = level
    
    def __lt__(self, other):
        return self.level < other.level
    
    def __gt__(self, other):
        return self.level > other.level
    
    def __ge__(self, other):
        return self.level >= other.level

    def __repr__(self):
        return "{}, skill: {}, level: {}".format(self.contributor.name, self.skill, self.level)


if __name__ == "__main__":
    contributors, projects = get_input()

    skills_names = set()
    for contributor in contributors:
        contributor: Contributor
        for skill in contributor.skills:
            skills_names.add(skill)
    
    developer_by_skill_tree = {}
    for skill in skills_names:
        developer_by_skill_tree[skill] = BinaryTree()
    for developer in contributors:
        developer: Contributor
        for skill in developer.skills:
            # developer_by_skill_tree[skill]: BinaryTree
            developer_by_skill_tree[skill].insert(Node(ContributorSkillLevel(developer, skill, developer.skills[skill])))
    
    list_of_interesting_days = BinaryTree()
    list_of_interesting_days.insert(Node(InterestingDay(0, [])))

    jobs = sorted(projects, key=lambda x: x.best_before)
    jobs_assignments = []
    projects_served = set()

    while list_of_interesting_days.get_first_element() is not None:
        interesting_day = list_of_interesting_days.get_first_element().value
        list_of_interesting_days.delete(interesting_day)
        interesting_day: InterestingDay
        # Re-insert developers that finish on that day.
        for job_finishing in interesting_day.jobs_finishing:
            job_finishing: JobAssignment
            for contributor in job_finishing.contributors:
                contributor: Contributor
                for skill in contributor.contributor.skills:
                    developer_by_skill_tree[skill].insert(Node(ContributorSkillLevel(contributor.contributor, skill, contributor.contributor.skills[skill])))

        for project in jobs:
            if project.name not in projects_served:
                developers_used = set()
                project: Project
                job_assignment = JobAssignment(project, [], interesting_day.day)
                for skill, level in zip(project.roles_names, project.roles_levels):
                    # Look for a developer with the given skill level
                    for contributor in developer_by_skill_tree[skill].scan():
                        contributor_skill_level = contributor.value
                        contributor_skill_level: ContributorSkillLevel
                        if contributor_skill_level.contributor.skills[skill] >= level and contributor_skill_level.contributor.name not in developers_used:
                            job_assignment.contributors.append(contributor_skill_level)
                            developers_used.add(contributor_skill_level.contributor.name)
                            break  # AS soon as we find a good contributor stop here.
                
                if len(job_assignment.contributors) == len(project.roles_names):
                    projects_served.add(job_assignment.project.name)
                    jobs_assignments.append(job_assignment)
                    for contributor_skill_level in job_assignment.contributors:
                        for skill in contributor_skill_level.contributor.skills:
                            developer_by_skill_tree[skill].delete(contributor_skill_level)
                    new_interesting_day = list_of_interesting_days.search(
                        InterestingDay(job_assignment.project.days + interesting_day.day, []))
                    if new_interesting_day is not None:
                        new_interesting_day.jobs_finishing.append(job_assignment)
                    else:
                        new_interesting_day = InterestingDay(job_assignment.project.days + interesting_day.day, [job_assignment])
                        list_of_interesting_days.insert(Node(new_interesting_day))
    
    print(len(jobs_assignments))
    for ja in jobs_assignments:
        print(ja)
    
    
    
