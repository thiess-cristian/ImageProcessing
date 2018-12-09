#include "ImageModifierFactory.h"
#include "ImageModifierNames.h"

#include "HistogramEqualizer.h"
#include "BinaryImage.h"
#include "InvertColors.h"
#include "MirrorImage.h"
#include "OtsuBinarization.h"
#include "VectorMedianFilter.h"
#include "GaussFilter.h"
#include "Canny.h"
#include "Sobel.h"
#include "ZhangSuen.h"


ImageModifierFactory::ImageModifierFactory()
{
    m_imageModifiers[ImageModifierNames::BinaryImage] =                []() {return new BinaryImage; };
    m_imageModifiers[ImageModifierNames::InvertColors] =               []() {return new InvertColors; };
    m_imageModifiers[ImageModifierNames::MirrorImage] =                []() {return new MirrorImage; };
    m_imageModifiers[ImageModifierNames::ColorHistogramEqualization] = []() {return new HistogramEqualizer; };
    m_imageModifiers[ImageModifierNames::OtsuBinarization] =           []() {return new OtsuBinarization; };
    m_imageModifiers[ImageModifierNames::VectorMedianFilter3x3] =      []() {return new VectorMedianFilter(VectorMedianFilterGrid::GridSize::Grid3x3); };
    m_imageModifiers[ImageModifierNames::VectorMedianFilter5x5] =      []() {return new VectorMedianFilter(VectorMedianFilterGrid::GridSize::Grid5x5); };
    m_imageModifiers[ImageModifierNames::Canny] =                      []() {return new Canny(); };
    m_imageModifiers[ImageModifierNames::GaussFilter] =                []() {return new GaussFilter(); };
    m_imageModifiers[ImageModifierNames::Sobel] =                      []() {return new Sobel(); };
    m_imageModifiers[ImageModifierNames::ZhangSuen] =                  []() {return new ZhangSuen(); };
}

ImageModifierFactory::~ImageModifierFactory()
{

}

IImageModifier * ImageModifierFactory::createNewImageModifier(const std::string& name) const
{
    return m_imageModifiers.at(name)(); //cant do [] because of const function
}
