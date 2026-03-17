from glob import glob
from os import system
from os.path import join
from sys import argv



curr_dir, task, *args = argv
"curr_dir should be "
p_tasks = join(
    "C:\\", "main_repos", "learn", "uust_YaP", "YaP", "1st_course"
)
p_builds = join(p_tasks, "bin")
p_gxx = join("C:\\", "mingw64", "bin", "g++.exe")

if task[-4:] == ".cpp": 
    task = task[:-4]

if task[:2] in ".\\ ./".split():
    task = task[2:]

print(task)
variants_to_run = glob(pathname=f"{task}.cpp", root_dir=p_tasks)

task_to_run = variants_to_run[0]
if variants_to_run.__len__() > 1:
    print("\n WARNING: Произошла Хрень, но нам похуй")


def run(gp_task, gp_build, args=tuple()):
    p1 = f'{p_gxx} "{gp_task}" -o \'{gp_build}\'';
    p2 = f'"{gp_build}" {" ".join(args)}'
    
    
    system(p1)
    print(p1)
    system(p2)
    print(p2)


run(join(p_tasks, task_to_run), join(p_builds, task_to_run[:-4] + ".exe"), args)
