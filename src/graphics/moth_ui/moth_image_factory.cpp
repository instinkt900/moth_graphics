#include "common.h"
#include "moth_graphics/graphics/moth_ui/moth_image_factory.h"
#include "moth_graphics/graphics/moth_ui/moth_image.h"

namespace moth_graphics::graphics {
    MothImageFactory::MothImageFactory(graphics::TextureFactory& factoryImpl)
        : m_factoryImpl(factoryImpl) {
    }

    std::unique_ptr<::moth_ui::IImage> MothImageFactory::GetImage(::moth_ui::AssetId const& id) {
        // This backend loads loose files, so it reads the identity as a path. moth_ui
        // itself no longer says an identity is one.
        auto const path = id.path();
        auto texture = m_factoryImpl.GetTexture(path);
        if (!texture) {
            return nullptr;
        }
        auto const sourceRect = m_factoryImpl.GetTextureRect(path);
        return std::make_unique<MothImage>(Image{ texture, sourceRect });
    }
}
