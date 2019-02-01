An practice from <https://github.com/Gazler/githug>

It is a game about git operation from easy to hard, so Let's start.

## Mission 1 - git init

```
git init
```

## Mission 2 - git config

```
#local
git config --local user.name "xxx" 
git config --local user.email "xxx"

#global
git config --global user.name "xxx" 
git config --global user.email "xxx"
```

## Mission 3 - git add

```
git add xxx
# add all file
git add --all
```

## Mission 4 - git commit

```
git commit -m "first commit"
```

## Mission 5 - git clone

```
git clone <https://github.com/Gazler/cloneme>
```

## Mission 6-git clone to folder

```
git clone <https://github.com/Gazler/cloneme> my_cloned_repo
```

## Mission 7 - ignore file

```
# ignore all files ending in ".swp"
echo "*.swp" >> .gitignore
```

## Mission 8 - include a specific file

```
# ignore all *.a except lib.a
# modify .gitignore
*.a
!lib.a
```

## Mission 9 - git status

```
# use to see file's status
git status
```

## Mission 10 - number of files committed

```
# only files add by git will be committed
```

## Mission 11 - git rm

```
git rm xxx
```

## Mission 12 - git reset

```
# git add a file accidentally, cancel it
git reset xxx
```

## Mission 13 - git stash

```
# want to save changes but don't want to commit
# save
git stash
# restore change
git stash pop

# git stash use structure like stack, so it's a LIFO
```

## Mission 14 - git mv

```
# move or rename a file
git mv old_name new_name
```

## Mission 15 - git move

```
# move file to src
mkdir src
git mv *.html src
```

## Mission 16 - git log

```
# see git log
git log
```

## Mission 17 - git tag

```
# tag current commit as a tag_name
git tag tag_name
```

## Mission 18 - push tag

```
# push tag_name to remote
git push origin tag_name
```

## Mission 19 - git commit amend

```
# modify commit message
# use vim as default editor
# git config --global core.editor vim
git commit --amend

# forget to add one file
git add xxx
git commit --amend
# will auto add the file to the last commit
```

## Mission 20  - git commit —date

```
# commit in a furture time
git commit -m "xxx" --date="2019-02-02"
```

## Mission 21 - git reset

```
# cancle git add
git reset HEAD xxx_file
```

## Mission 22 - git reset —soft

```
# cancle the last commit
git reset --soft commit_id

# commit_id is the id before the commit you cancle.
# like commit 2, commit 1, want to cancle commit 2, 
# so commit_id should be commit 1
```

## Mission 23 - git checkout

```
# discard change
git checkout xxx_file
```

