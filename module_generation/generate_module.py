
import shutil
import sys
import os

THIS_DIR = os.path.dirname(__file__)

PROJECT_ROOT_DIR = os.path.abspath(
        os.path.join(
            THIS_DIR,
            ".."
        )
    )

if len(sys.argv) < 2:
    print("Please provide a module name")
    sys.exit(1)

module_name = sys.argv[1]

# Create directory for the module
os.makedirs(
    os.path.join(
        PROJECT_ROOT_DIR,
        module_name
    ),
    exist_ok=True
)

# Copy CMAKE files into it
shutil.copytree(
    os.path.join(
        THIS_DIR,
        "module_common_files"
    ),
    os.path.join(
        PROJECT_ROOT_DIR,
        module_name
    ),
    dirs_exist_ok=True
)
