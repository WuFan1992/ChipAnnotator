import subprocess
import os

def processDirectory(directory):
	for root, dirs, files in os.walk(directory):
		for i in files:
			if i.endswith(".cpp") or i.endswith(".hpp"):
				print("formatting " + os.path.join(root, i))
				subprocess.call(["clang-format", "-i", os.path.join(root, i)])

root_path=os.getcwd()

processDirectory(root_path)
