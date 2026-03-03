from glob import glob
from os import system
from os.path import join
from sys import argv

curr_dir, task, *args = argv
"curr_dir should be "
p_tasks = join(
    "C:\\", "repos", "user", "CXX_projects", "main_cmake", "YaP", "1st course"
)
p_builds = join(p_tasks, "builds")
if task[-4:] == ".cpp": 
    task = task[:-4]
print(task)
variants_to_run = glob(pathname=f"{task}.cpp", root_dir=p_tasks)

task_to_run = variants_to_run[0]
if variants_to_run.__len__() > 1:
    print("\n WARNING: Произошла Хрень, но нам похуй")


def run(gp_task, gp_build, args=tuple()):
    system(f'g++.exe -std=c++20 "{gp_task}" -o "{gp_build}"')
    system(f'"{gp_build}" {" ".join(args)}')


run(join(p_tasks, task_to_run), join(p_builds, task_to_run[:-4]), args)
