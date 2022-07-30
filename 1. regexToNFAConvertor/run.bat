echo "Compiling CPP Code"
g++ regexToNfa.cpp -o regexToNfa
echo "Executing CPP Code"
start regexToNfa.exe
echo "Visualizing the graph"
python graphicalOutput.py