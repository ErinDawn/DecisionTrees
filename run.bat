::batch file to run decision tree
::sends the meta-data to it as (expected) user input
::in this case irisInput.txt
::sends the output to a new file in the 'outputs' folder

main.exe< exampleInput.txt > outputs/_outputBball.txt

:: wait for user to push enter to continue
pause

main.exe< irisInput.txt > outputs/_outputIris.txt
