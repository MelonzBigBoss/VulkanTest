mkdir build

mkdir "build/VertexShader"
mkdir "build/FragShader"

glslc src/VertexShader/triangle.vert -o build/VertexShader/vert.spv
glslc src/FragShader/triangle.frag -o build/FragShader/frag.spv


cd build
cmake -S ../

pause