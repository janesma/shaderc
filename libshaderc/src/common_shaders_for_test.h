// Copyright 2015 The Shaderc Authors. All rights reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef COMMON_SHADERS_FOR_TESTS_H_
#define COMMON_SHADERS_FOR_TESTS_H_

#ifdef __cplusplus
extern "C" {
#endif

// The minimal shader, without a version directive.
const char kMinimalShaderWithoutVersion[] = "void main(){}";
// The minimal shader, with a version directive.
const char kMinimalShader[] =
    "#version 140\n"
    "void main(){}";
const char kMinimalShaderWithMacro[] =
    "#version 140\n"
    "#define E main\n"
    "void E(){}\n";

// The minimal shader that needs valueless predefinition of 'E' to compile.
const char kValuelessPredefinitionShader[] =
    "#version 140\n"
    "#ifdef E\n"
    "void main(){}\n"
    "#else\n"
    "#error\n"
    "#endif";

// By default the compiler will emit a warning on line 2 complaining
// that 'float' is a deprecated attribute in version 130.  Use verison 140
// because some versions of glslang will error out for a too-low version
// when generating SPIR-V.
const char kDeprecatedAttributeShader[] =
    "#version 140\n"
    "attribute float x;\n"
    "void main() {}\n";

// By default the compiler will emit a warning as version 550 is an unknown
// version.
const char kMinimalUnknownVersionShader[] =
    "#version 550\n"
    "void main() {}\n";

// gl_ClipDistance doesn't exist in es profile (at least until 3.10).
const char kCoreVertShaderWithoutVersion[] =
    "void main() {\n"
    "gl_ClipDistance[0] = 5.;\n"
    "}\n";

// Generated debug information should contain the name of the vector:
// debug_info_sample.
const char kMinimalDebugInfoShader[] =
    "#version 140\n"
    "void main(){\n"
    "vec2 debug_info_sample = vec2(1.0,1.0);\n"
    "}\n";

// Compiler should generate two errors.
const char kTwoErrorsShader[] =
    "#version 150\n"
    "#error\n"
    "#error\n"
    "void main(){}\n";

// Compiler should generate two warnings.
const char kTwoWarningsShader[] =
    "#version 140\n"
    "attribute float x;\n"
    "attribute float y;\n"
    "void main(){}\n";

// A shader that compiles under OpenGL compatibility profile rules,
// but not OpenGL core profile rules.
const char kOpenGLCompatibilityFragmentShader[] =
    R"(#version 100
     uniform highp sampler2D tex;
     void main() {
       gl_FragColor = texture2D(tex, vec2(0.0,0.0));
     })";

// A shader that compiles under OpenGL core profile rules.
const char kOpenGLVertexShader[] =
    R"(#version 330
       void main() { int t = gl_VertexID; })";

// Empty 310 es shader. It is valid for vertex, fragment, compute shader kind.
const char kEmpty310ESShader[] =
    "#version 310 es\n"
    "void main() {}\n";

// Vertex only shader.
const char kVertexOnlyShader[] =
    "#version 310 es\n"
    "void main() {\n"
    "    gl_Position = vec4(1.);\n"
    "}";

// TessControl only shader.
const char kTessControlOnlyShader[] =
    "#version 440 core\n"
    "layout(vertices = 3) out;\n"
    "void main() { }";

// TessEvaluation only shader.
const char kTessEvaluationOnlyShader[] =
    "#version 440 core\n"
    "layout(triangles) in;\n"
    "void main() { }";

// Geometry only shader.
const char kGeometryOnlyShader[] =
    "#version 150 core\n"
    "layout (triangles) in;\n"
    "layout (line_strip, max_vertices = 4) out;\n"
    "void main() { }";

// Vertex only shader with #pragma annotation.
const char kVertexOnlyShaderWithPragma[] =
    "#version 310 es\n"
    "#pragma shader_stage(vertex)\n"
    "void main() {\n"
    "    gl_Position = vec4(1.);\n"
    "}";

// Fragment only shader with #pragma annotation.
const char kFragmentOnlyShaderWithPragma[] =
    "#version 310 es\n"
    "#pragma shader_stage(fragment)\n"
    "void main() {\n"
    "    gl_FragDepth = 10.;\n"
    "}";

// TessControl only shader with #pragma annotation.
const char kTessControlOnlyShaderWithPragma[] =
    "#version 440 core\n"
    "#pragma shader_stage(tesscontrol)\n"
    "layout(vertices = 3) out;\n"
    "void main() { }";

// TessEvaluation only shader with #pragma annotation.
const char kTessEvaluationOnlyShaderWithPragma[] =
    "#version 440 core\n"
    "#pragma shader_stage(tesseval)\n"
    "layout(triangles) in;\n"
    "void main() { }";

// Geometry only shader with #pragma annotation.
const char kGeometryOnlyShaderWithPragma[] =
    "#version 150 core\n"
    "#pragma shader_stage(geometry)\n"
    "layout (triangles) in;\n"
    "layout (line_strip, max_vertices = 4) out;\n"
    "void main() { }";

// Compute only shader with #pragma annotation.
const char kComputeOnlyShaderWithPragma[] =
    "#version 310 es\n"
    "#pragma shader_stage(compute)\n"
    "void main() {\n"
    "    uvec3 temp = gl_WorkGroupID;\n"
    "}";

// Vertex only shader with invalid #pragma annotation.
const char kVertexOnlyShaderWithInvalidPragma[] =
    "#version 310 es\n"
    "#pragma shader_stage(fragment)\n"
    "void main() {\n"
    "    gl_Position = vec4(1.);\n"
    "}";

// Parts of a valid disassembly of a minimal shader.  We only check certain
// parts since Glslang code generation changes in incidental ways.
const char* kMinimalShaderDisassemblySubstrings[] = {
    "; SPIR-V\n"
    "; Version: 1.0\n"
    "; Generator: Khronos Glslang Reference Front End; 1\n"
    "; Bound:",

    "               OpCapability Shader\n",
    "          %1 = OpExtInstImport \"GLSL.std.450\"\n",
    "               OpMemoryModel Logical GLSL450\n",
    "               OpReturn\n",
    "               OpFunctionEnd\n"};

const char kMinimalShaderAssembly[] = R"(
    ; SPIR-V
    ; Version: 1.0
    ; Generator: Khronos Glslang Reference Front End; 1
    ; Bound: 6
    ; Schema: 0

         OpCapability Shader
    %1 = OpExtInstImport "GLSL.std.450"
         OpMemoryModel Logical GLSL450
         OpEntryPoint Vertex %4 "main"
         OpSource ESSL 310
         OpName %4 "main"
    %2 = OpTypeVoid
    %3 = OpTypeFunction %2
    %4 = OpFunction %2 None %3
    %5 = OpLabel
         OpReturn
         OpFunctionEnd)";

#ifdef __cplusplus
}
#endif  // __cplusplus

#endif  // COMMON_SHADERS_FOR_TESTS_H_
