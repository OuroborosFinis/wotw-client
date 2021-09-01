#include <utils/shaders.h>

#include <Common/ext.h>
#include <Il2CppModLoader/interception_macros.h>
#include <Il2CppModLoader/il2cpp_helpers.h>
#include <Il2CppModLoader/il2cpp_math.h>

namespace shaders
{
    STATIC_IL2CPP_BINDING(, UberShaderAPI, bool, HasProperty, 
        (app::Renderer* renderer, app::UberShaderProperty_Texture__Enum prop, app::UberShaderProperties_TextureSuffixType__Enum suffix));
    NAMED_STATIC_IL2CPP_BINDING_OVERLOAD(, UberShaderAPI, bool, HasProperty, HasPropertyColor,
        (app::Renderer* renderer, app::UberShaderProperty_Color__Enum prop), (UnityEngine:Renderer, UberShaderProperty_Color));
    NAMED_STATIC_IL2CPP_BINDING_OVERLOAD(, UberShaderAPI, bool, HasProperty, HasPropertyVector,
        (app::Renderer* renderer, app::UberShaderProperty_Vector__Enum prop), (UnityEngine:Renderer, UberShaderProperty_Vector));
    NAMED_STATIC_IL2CPP_BINDING_OVERLOAD(, UberShaderAPI, bool, HasProperty, HasPropertyFloat,
        (app::Renderer* renderer, app::UberShaderProperty_Float__Enum prop), (UnityEngine:Renderer, UberShaderProperty_Float));

    ShaderInfo get_info(app::Renderer* renderer)
    {
        ShaderInfo info;
        for (int i = 0; i < static_cast<int>(app::UberShaderProperty_Texture__Enum_TotalTextureProperties); ++i)
        {
            auto value = static_cast<app::UberShaderProperty_Texture__Enum>(i);
            for (int j = 0 ; j < 6; ++j)
            {
                auto suffix = static_cast<app::UberShaderProperties_TextureSuffixType__Enum>(j);
                if (UberShaderAPI::HasProperty(renderer, value, suffix))
                    info.textures.push_back(std::make_pair(value, suffix));
            }
        }

        for (int i = 0; i < static_cast<int>(app::UberShaderProperty_Color__Enum_TotalColorProperties); ++i)
        {
            auto value = static_cast<app::UberShaderProperty_Color__Enum>(i);
            if (UberShaderAPI::HasPropertyColor(renderer, value))
                info.colors .push_back(value);
        }

        for (int i = 0; i < static_cast<int>(app::UberShaderProperty_Vector__Enum_TotalVectorProperties); ++i)
        {
            auto value = static_cast<app::UberShaderProperty_Vector__Enum>(i);
            if (UberShaderAPI::HasPropertyVector(renderer, value))
                info.vectors.push_back(value);
        }

        for (int i = 0; i < static_cast<int>(app::UberShaderProperty_Float__Enum_TotalFloatProperties); ++i)
        {
            auto value = static_cast<app::UberShaderProperty_Float__Enum>(i);
            if (UberShaderAPI::HasPropertyFloat(renderer, value))
                info.floats.push_back(value);
        }

        return info;
    }
}
