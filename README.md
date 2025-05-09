# miniRT
Mini raytracing


Useful link

tutorial
https://www.youtube.com/watch?v=E6e_hQ5LQDE



extension
GitLens

CREATE BRANCH:

git branch

if not in main:

git checkout main
git checkout -b <my_branch_name>
git add, commit, push



MERGE YOUR BRANCH stuff to main:
After git push, go to github and press create pull request, accept everything.
If there are merge conflicts there, cancel that. You need to merge latest main
version to your branch before that and solve the conflicts:

make sure you are in your branch
get last main version:
git checkout main
git pull
git checkout your_branch
git merge main
Then you have to solve conflicts by keeping incoming version, your version or both.
All conflicts are showed in vscode with red exclamation mark next to filename.
After selecting in code what to keep, you have to press somwhere at bottom right
something like "accept changes" or "solve conflicts".
After all solved
git add, commit, push.
Now pull request is possible with no conflicts.



If you accidentally started WORK IN MAIN but havent done git add, you can just create branch from current situotion:
git checkout -b your_new_branch_name


If you want to GO BACK in commits and It's ok to lose current progress:
git reset --hard <commit-hash>

If you want to GO BACK in commits and It's NOT ok to lose current progress:
git checkout <commit-hash>
git checkout -b <new-branch-name>

Get latest information about branches to gitlens without pulling anything:
git fetch

