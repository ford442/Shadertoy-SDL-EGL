#include "../../include/shader/shader_webgpu.hpp"

const TBuiltInResource DefaultTBuiltInResource = {
    /* .MaxLights = */ 32,
    /* .MaxClipPlanes = */ 6,
    /* .MaxTextureUnits = */ 32,
    /* .MaxTextureCoords = */ 32,
    /* .MaxVertexAttribs = */ 64,
    /* .MaxVertexUniformComponents = */ 4096,
    /* .MaxVaryingFloats = */ 64,
    /* .MaxVertexTextureImageUnits = */ 32,
    /* .MaxCombinedTextureImageUnits = */ 80,
    /* .MaxTextureImageUnits = */ 32,
    /* .MaxFragmentUniformComponents = */ 4096,
    /* .MaxDrawBuffers = */ 32,
    /* .MaxVertexUniformVectors = */ 128,
    /* .MaxVaryingVectors = */ 8,
    /* .MaxFragmentUniformVectors = */ 16,
    /* .MaxVertexOutputVectors = */ 16,
    /* .MaxFragmentInputVectors = */ 15,
    /* .MinProgramTexelOffset = */ -8,
    /* .MaxProgramTexelOffset = */ 7,
    /* .MaxClipDistances = */ 8,
    /* .MaxComputeWorkGroupCountX = */ 65535,
    /* .MaxComputeWorkGroupCountY = */ 65535,
    /* .MaxComputeWorkGroupCountZ = */ 65535,
    /* .MaxComputeWorkGroupSizeX = */ 1024,
    /* .MaxComputeWorkGroupSizeY = */ 1024,
    /* .MaxComputeWorkGroupSizeZ = */ 64,
    /* .MaxComputeUniformComponents = */ 1024,
    /* .MaxComputeTextureImageUnits = */ 16,
    /* .MaxComputeImageUniforms = */ 8,
    /* .MaxComputeAtomicCounters = */ 8,
    /* .MaxComputeAtomicCounterBuffers = */ 1,
    /* .MaxVaryingComponents = */ 60,
    /* .MaxVertexOutputComponents = */ 64,
    /* .MaxGeometryInputComponents = */ 64,
    /* .MaxGeometryOutputComponents = */ 128,
    /* .MaxFragmentInputComponents = */ 128,
    /* .MaxImageUnits = */ 8,
    /* .MaxCombinedImageUnitsAndFragmentOutputs = */ 8,
    /* .MaxCombinedShaderOutputResources = */ 8,
    /* .MaxImageSamples = */ 0,
    /* .MaxVertexImageUniforms = */ 0,
    /* .MaxTessControlImageUniforms = */ 0,
    /* .MaxTessEvaluationImageUniforms = */ 0,
    /* .MaxGeometryImageUniforms = */ 0,
    /* .MaxFragmentImageUniforms = */ 8,
    /* .MaxCombinedImageUniforms = */ 8,
    /* .MaxGeometryTextureImageUnits = */ 16,
    /* .MaxGeometryOutputVertices = */ 256,
    /* .MaxGeometryTotalOutputComponents = */ 1024,
    /* .MaxGeometryUniformComponents = */ 1024,
    /* .MaxGeometryVaryingComponents = */ 64,
    /* .MaxTessControlInputComponents = */ 128,
    /* .MaxTessControlOutputComponents = */ 128,
    /* .MaxTessControlTextureImageUnits = */ 16,
    /* .MaxTessControlUniformComponents = */ 1024,
    /* .MaxTessControlTotalOutputComponents = */ 4096,
    /* .MaxTessEvaluationInputComponents = */ 128,
    /* .MaxTessEvaluationOutputComponents = */ 128,
    /* .MaxTessEvaluationTextureImageUnits = */ 16,
    /* .MaxTessEvaluationUniformComponents = */ 1024,
    /* .MaxTessPatchComponents = */ 120,
    /* .MaxPatchVertices = */ 32,
    /* .MaxTessGenLevel = */ 64,
    /* .MaxViewports = */ 16,
    /* .MaxVertexAtomicCounters = */ 0,
    /* .MaxTessControlAtomicCounters = */ 0,
    /* .MaxTessEvaluationAtomicCounters = */ 0,
    /* .MaxGeometryAtomicCounters = */ 0,
    /* .MaxFragmentAtomicCounters = */ 8,
    /* .MaxCombinedAtomicCounters = */ 8,
    /* .MaxAtomicCounterBindings = */ 1,
    /* .MaxVertexAtomicCounterBuffers = */ 0,
    /* .MaxTessControlAtomicCounterBuffers = */ 0,
    /* .MaxTessEvaluationAtomicCounterBuffers = */ 0,
    /* .MaxGeometryAtomicCounterBuffers = */ 0,
    /* .MaxFragmentAtomicCounterBuffers = */ 1,
    /* .MaxCombinedAtomicCounterBuffers = */ 1,
    /* .MaxAtomicCounterBufferSize = */ 16384,
    /* .MaxTransformFeedbackBuffers = */ 4,
    /* .MaxTransformFeedbackInterleavedComponents = */ 64,
    /* .MaxCullDistances = */ 8,
    /* .MaxCombinedClipAndCullDistances = */ 8,
    /* .MaxSamples = */ 4,
    /* .maxMeshOutputVerticesNV = */ 256,
    /* .maxMeshOutputPrimitivesNV = */ 512,
    /* .maxMeshWorkGroupSizeX_NV = */ 32,
    /* .maxMeshWorkGroupSizeY_NV = */ 1,
    /* .maxMeshWorkGroupSizeZ_NV = */ 1,
    /* .maxTaskWorkGroupSizeX_NV = */ 32,
    /* .maxTaskWorkGroupSizeY_NV = */ 1,
    /* .maxTaskWorkGroupSizeZ_NV = */ 1,
    /* .maxMeshViewCountNV = */ 4,
    /* .maxDualSourceDrawBuffersEXT = */ 1,

    /* .limits = */ {
        /* .nonInductiveForLoops = */ 1,
        /* .whileLoops = */ 1,
        /* .doWhileLoops = */ 1,
        /* .generalUniformIndexing = */ 1,
        /* .generalAttributeMatrixVectorIndexing = */ 1,
        /* .generalVaryingIndexing = */ 1,
        /* .generalSamplerIndexing = */ 1,
        /* .generalVariableIndexing = */ 1,
        /* .generalConstantMatrixVectorIndexing = */ 1,
    }};

static bool initialized = false;

extern "C" {

/*
 * Takes in a GLSL shader as a string and converts it to SPIR-V in binary form.
 *
 * |glsl|          Null-terminated string containing the shader to be converted.
 * |stage_int|     Magic number indicating the type of shader being processed.
*                  Legal values are as follows:
 *                   Vertex = 0
 *                   Fragment = 4
 *                   Compute = 5
 * |gen_debug|     Flag to indicate if debug information should be generated.
 * |spirv|         Output parameter for a pointer to the resulting SPIR-V data.
 * |spirv_len|     Output parameter for the length of the output binary buffer.
 *
 * Returns a void* pointer which, if not null, must be destroyed by
 * destroy_output_buffer.o. (This is not the same pointer returned in |spirv|.)
 * If null, the compilation failed.
 */
EMSCRIPTEN_KEEPALIVE
void* convert_glsl_to_spirv(const char* glsl,
                            int stage_int,
                            bool gen_debug,
                            glslang::EShTargetLanguageVersion spirv_version,
                            uint32_t** spirv,
                            size_t* spirv_len)
{
    if (glsl == nullptr) {
        fprintf(stderr, "Input pointer null\n");
        return nullptr;
    }
    if (spirv == nullptr || spirv_len == nullptr) {
        fprintf(stderr, "Output pointer null\n");
        return nullptr;
    }
    *spirv = nullptr;
    *spirv_len = 0;

    if (stage_int != 0 && stage_int != 4 && stage_int != 5) {
        fprintf(stderr, "Invalid shader stage\n");
        return nullptr;
    }
    EShLanguage stage = static_cast<EShLanguage>(stage_int);
    switch (spirv_version) {
        case glslang::EShTargetSpv_1_0:
        case glslang::EShTargetSpv_1_1:
        case glslang::EShTargetSpv_1_2:
        case glslang::EShTargetSpv_1_3:
        case glslang::EShTargetSpv_1_4:
        case glslang::EShTargetSpv_1_5:
            break;
        default:
            fprintf(stderr, "Invalid SPIR-V version number\n");
            return nullptr;
    }

    if (!initialized) {
        glslang::InitializeProcess();
        initialized = true;
    }

    glslang::TShader shader(stage);
    shader.setStrings(&glsl, 1);
    shader.setEnvInput(glslang::EShSourceGlsl, stage, glslang::EShClientVulkan, 100);
    shader.setEnvClient(glslang::EShClientVulkan, glslang::EShTargetVulkan_1_0);
    shader.setEnvTarget(glslang::EShTargetSpv, spirv_version);
    if (!shader.parse(&DefaultTBuiltInResource, 100, true, EShMsgDefault)) {
        fprintf(stderr, "Parse failed\n");
        fprintf(stderr, "%s\n", shader.getInfoLog());
        return nullptr;
    }

    glslang::TProgram program;
    program.addShader(&shader);
    if (!program.link(EShMsgDefault)) {
        fprintf(stderr, "Link failed\n");
        fprintf(stderr, "%s\n", program.getInfoLog());
        return nullptr;
    }

    glslang::SpvOptions spvOptions;
    spvOptions.generateDebugInfo = gen_debug;
    spvOptions.optimizeSize = false;
    spvOptions.disassemble = false;
    spvOptions.validate = false;

    std::vector<uint32_t>* output = new std::vector<uint32_t>;
    glslang::GlslangToSpv(*program.getIntermediate(stage), *output, nullptr, &spvOptions);

    *spirv_len = output->size();
    *spirv = output->data();
    return output;
}

/*
 * Destroys a buffer created by convert_glsl_to_spirv
 */
EMSCRIPTEN_KEEPALIVE
void destroy_output_buffer(void* p)
{
    delete static_cast<std::vector<uint32_t>*>(p);
}

}  // extern "C"


Run run;

boost::function<EM_BOOL(void)>strtr=[](void){
run.strt();
return EM_TRUE;
};

boost::function<EM_BOOL(void)>swpp=[](void){
run.swap();
return EM_TRUE;
};

extern "C" {

EM_BOOL str(){
strtr();
return EM_TRUE;
}

EM_BOOL swp(){
swpp();
return EM_TRUE;
}

EM_BOOL ud(){
run.uniDOWN();
return EM_TRUE;
}

EM_BOOL uu(){
run.uniUP();
return EM_TRUE;
}

EM_BOOL vd(){
run.viewDOWN();
return EM_TRUE;
}

EM_BOOL vu(){
run.viewUP();
return EM_TRUE;
}

EM_BOOL mu(){
run.moveUP();
return EM_TRUE;
}

EM_BOOL md(){
run.moveDOWN();
return EM_TRUE;
}

EM_BOOL ml(){
run.moveLEFT();
return EM_TRUE;
}

EM_BOOL mr(){
run.moveRIGHT();
return EM_TRUE;
}

}
