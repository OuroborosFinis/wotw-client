#include <utils/shaders.h>

#include <Common/ext.h>
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

    STATIC_IL2CPP_BINDING(, UberShaderAPI, void, SetTexture, (app::Renderer* renderer, app::UberShaderProperty_Texture__Enum prop, void const* texture));
    STATIC_IL2CPP_BINDING(, UberShaderAPI, void, SetTextureScale, (app::Renderer* renderer, app::UberShaderProperty_Texture__Enum prop, app::Vector2 const* scale));
    STATIC_IL2CPP_BINDING(, UberShaderAPI, void, SetTextureOffset, (app::Renderer* renderer, app::UberShaderProperty_Texture__Enum prop, app::Vector2 const* offset));
    STATIC_IL2CPP_BINDING(, UberShaderAPI, void, SetTextureAtlasUVs, (app::Renderer* this_ptr, app::UberShaderProperty_Texture__Enum p, app::Vector4 const* atlas_uvs));
    STATIC_IL2CPP_BINDING(, UberShaderAPI, void, SetTextureScrollRotData, (app::Renderer* this_ptr, app::UberShaderProperty_Texture__Enum p, app::Vector4 const* scroll_rot));
    STATIC_IL2CPP_BINDING(, UberShaderAPI, void, SetVector, (app::Renderer* this_ptr, app::UberShaderProperty_Vector__Enum p, app::Vector4 const* vec));
    STATIC_IL2CPP_BINDING(, UberShaderAPI, void, SetColor, (app::Renderer* renderer, app::UberShaderProperty_Color__Enum prop, app::Color const* color));
    STATIC_IL2CPP_BINDING(, UberShaderAPI, void, SetFloat, (app::Renderer* renderer, app::UberShaderProperty_Float__Enum prop, float value));
    STATIC_IL2CPP_BINDING(, UberShaderAPI, void, SetAlpha, (app::Renderer* this_ptr, app::Material* material, app::UberShaderProperty_Color__Enum p, float color));

    STATIC_IL2CPP_BINDING(, UberShaderAPI, app::Material*, GetEditableMaterial, (app::Renderer* this_ptr));
    STATIC_IL2CPP_BINDING(, UberShaderAPI, app::Material*, GetSharedMaterial, (app::Renderer* this_ptr));
    STATIC_IL2CPP_BINDING(, UberShaderAPI, app::Texture*, GetTexture, (app::Renderer* this_ptr, app::UberShaderProperty_Texture__Enum p));
    STATIC_IL2CPP_BINDING(, UberShaderAPI, app::Vector2, GetTextureScale, (app::Renderer* this_ptr, app::UberShaderProperty_Texture__Enum p));
    STATIC_IL2CPP_BINDING(, UberShaderAPI, app::Vector2, GetTextureOffset, (app::Renderer* this_ptr, app::UberShaderProperty_Texture__Enum p));
    STATIC_IL2CPP_BINDING(, UberShaderAPI, app::Vector4, GetTextureAtlasUVs, (app::Renderer* this_ptr, app::UberShaderProperty_Texture__Enum p));
    STATIC_IL2CPP_BINDING(, UberShaderAPI, app::Vector4, GetTextureScrollRotData, (app::Renderer* this_ptr, app::UberShaderProperty_Texture__Enum p));
    STATIC_IL2CPP_BINDING(, UberShaderAPI, app::Vector4, GetVector, (app::Renderer* this_ptr, app::UberShaderProperty_Vector__Enum p));
    STATIC_IL2CPP_BINDING(, UberShaderAPI, app::Color, GetColor, (app::Renderer* renderer, app::UberShaderProperty_Color__Enum prop));
    STATIC_IL2CPP_BINDING(, UberShaderAPI, float, GetFloat, (app::Renderer* renderer, app::UberShaderProperty_Float__Enum prop));

    STATIC_IL2CPP_BINDING(UnityEngine, Shader, app::Shader*, Find, (app::String* name));

    NAMED_IL2CPP_BINDING_OVERLOAD(UnityEngine, Material, void, .ctor, ctor_shader, (app::Material* this_ptr, app::Shader* shader), (UnityEngine:Shader));
    NAMED_IL2CPP_BINDING_OVERLOAD(UnityEngine, Material, void, .ctor, ctor, (app::Material* this_ptr, app::Material* other), (UnityEngine:Material));
    IL2CPP_BINDING(UnityEngine, Material, void, CopyPropertiesFromMaterial, (app::Material* this_ptr, app::Material* other));
    IL2CPP_BINDING(UnityEngine, Material, app::Shader*, get_shader, (app::Material* this_ptr));

    ShaderInfo get_info(app::Renderer* renderer)
    {
        ShaderInfo info;
        for (int i = 0; i < static_cast<int>(app::UberShaderProperty_Texture__Enum_TotalTextureProperties); ++i)
        {
            auto value = static_cast<app::UberShaderProperty_Texture__Enum>(i);
            TextureBlock block;
            for (int j = 0 ; j < 6; ++j)
            {
                auto suffix = static_cast<app::UberShaderProperties_TextureSuffixType__Enum>(j);
                if (UberShaderAPI::HasProperty(renderer, value, suffix))
                    block.properties.push_back(suffix);
            }

            if (!block.properties.empty())
            {
                block.offset = UberShaderAPI::GetTextureOffset(renderer, value);
                block.scale = UberShaderAPI::GetTextureScale(renderer, value);
                block.uvs = UberShaderAPI::GetTextureAtlasUVs(renderer, value);
                block.scroll_rot = UberShaderAPI::GetTextureScrollRotData(renderer, value);
                block.texture = UberShaderAPI::GetTexture(renderer, value);
                info.textures.push_back({ value, block });
            }
        }

        for (int i = 0; i < static_cast<int>(app::UberShaderProperty_Color__Enum_TotalColorProperties); ++i)
        {
            auto value = static_cast<app::UberShaderProperty_Color__Enum>(i);
            if (UberShaderAPI::HasPropertyColor(renderer, value))
                info.colors.push_back({ value, UberShaderAPI::GetColor(renderer, value) });
        }

        for (int i = 0; i < static_cast<int>(app::UberShaderProperty_Vector__Enum_TotalVectorProperties); ++i)
        {
            auto value = static_cast<app::UberShaderProperty_Vector__Enum>(i);
            if (UberShaderAPI::HasPropertyVector(renderer, value))
                info.vectors.push_back({ value, UberShaderAPI::GetVector(renderer, value) });
        }

        for (int i = 0; i < static_cast<int>(app::UberShaderProperty_Float__Enum_TotalFloatProperties); ++i)
        {
            auto value = static_cast<app::UberShaderProperty_Float__Enum>(i);
            if (UberShaderAPI::HasPropertyFloat(renderer, value))
                info.floats.push_back({ value, UberShaderAPI::GetFloat(renderer, value) });
        }

        return info;
    }

    void set_info(app::Renderer* renderer, ShaderInfo const& info)
    {
        for (auto texture : info.textures)
        {
            auto type = texture.first;
            UberShaderAPI::SetTextureOffset(renderer, type, &texture.second.offset);
            UberShaderAPI::SetTextureScale(renderer, type, &texture.second.scale);
            UberShaderAPI::SetTextureAtlasUVs(renderer, type, &texture.second.uvs);
            UberShaderAPI::SetTextureScrollRotData(renderer, type, &texture.second.scroll_rot);
            UberShaderAPI::SetTexture(renderer, type, &texture.second.texture);
        }

        for (auto color : info.colors)
            UberShaderAPI::SetColor(renderer, color.first, &color.second);

        for (auto f : info.floats)
            UberShaderAPI::SetFloat(renderer, f.first, f.second);

        for (auto v : info.vectors)
            UberShaderAPI::SetVector(renderer, v.first, &v.second);
    }

    void apply(app::Renderer* renderer, ShaderInfo const& info)
    {
        set_info(renderer, info);
    }

    void set_shader(app::Renderer* renderer, app::Shader* shader, bool shared)
    {
        auto pinfo = shaders::get_info(renderer);
        auto mat = shared
            ? shaders::UberShaderAPI::GetSharedMaterial(renderer)
            : shaders::UberShaderAPI::GetEditableMaterial(renderer);
        il2cpp::invoke(mat, "set_shader", shader);
        set_info(renderer, pinfo);
    }

    app::Material* copy_material(app::Material* source)
    {
        auto instanced_material = il2cpp::create_object<app::Material>("UnityEngine", "Material");
        auto shader = Material::get_shader(source);
        Material::ctor_shader(instanced_material, shader);
        Material::CopyPropertiesFromMaterial(instanced_material, source);
        return instanced_material;
    }

    void make_material_unique(app::Renderer* renderer)
    {
        auto mat = shaders::UberShaderAPI::GetEditableMaterial(renderer);
        //auto new_mat = il2cpp::create_object<app::Material>("UnityEngine", "Material");
        //il2cpp::invoke(new_mat, ".ctor", mat);
        auto new_mat = copy_material(mat);
        il2cpp::invoke(renderer, "set_material", new_mat);
    }
}
