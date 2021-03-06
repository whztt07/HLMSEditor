/****************************************************************************
**
** Copyright (C) 2016 - 2017
**
** This file is generated by the Magus toolkit
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
****************************************************************************/

// Include
#include "constants.h"
#include "hlms_builder.h"
#include <QFile>
#include <QTextStream>
#include "OgreResourceGroupManager.h"
#include "OgreHlmsManager.h"
#include "OgreHlmsJson.h"

//****************************************************************************/
HlmsBuilder::HlmsBuilder(void)
{
}

//****************************************************************************/
HlmsBuilder::~HlmsBuilder(void)
{
}

//****************************************************************************/
HlmsNodeSamplerblock* HlmsBuilder::createSamplerNode(Magus::QtNodeEditor* nodeEditor)
{
    HlmsNodeSamplerblock* node = new HlmsNodeSamplerblock(NODE_TITLE_SAMPLERBLOCK);
    node->setType(NODE_TYPE_SAMPLERBLOCK);
    nodeEditor->addNode(node);
    return node;
}

//****************************************************************************/
HlmsNodeMacroblock* HlmsBuilder::createMacroNode(Magus::QtNodeEditor* nodeEditor)
{
    HlmsNodeMacroblock* node = new HlmsNodeMacroblock(NODE_TITLE_MACROBLOCK);
    node->setType(NODE_TYPE_MACROBLOCK);
    nodeEditor->addNode(node);
    return node;
}

//****************************************************************************/
HlmsNodeBlendblock* HlmsBuilder::createBlendNode(Magus::QtNodeEditor* nodeEditor)
{
    HlmsNodeBlendblock* node = new HlmsNodeBlendblock(NODE_TITLE_BLENDBLOCK);
    node->setType(NODE_TYPE_BLENDBLOCK);
    nodeEditor->addNode(node);
    return node;
}

//****************************************************************************/
void HlmsBuilder::enrichSamplerBlockGeneric (Ogre::HlmsSamplerblock* samplerblock,
                                             HlmsNodeSamplerblock* samplernode)
{
    // ******** Min filter ********
    samplerblock->mMinFilter = getFilterOptionFromIndex(samplernode->getTextureMinFilter());

    // ******** Mag filter ********
    samplerblock->mMagFilter = getFilterOptionFromIndex(samplernode->getTextureMagFilter());

    // ******** Mip filter ********
    samplerblock->mMipFilter = getFilterOptionFromIndex(samplernode->getTextureMipFilter());

    // ******** Texture addressing mode U ********
    samplerblock->mU = getTAMFromIndex(samplernode->getTextureAddressingModeU());

    // ******** Texture addressing mode V ********
    samplerblock->mV = getTAMFromIndex(samplernode->getTextureAddressingModeV());

    // ******** Texture addressing mode W ********
    samplerblock->mW = getTAMFromIndex(samplernode->getTextureAddressingModeW());

    // ******** Mip LOD Bias ********
    samplerblock->mMipLodBias = samplernode->getMipLodBias();

    // ******** Max Anisotropy ********
    samplerblock->mMaxAnisotropy = samplernode->getMaxAnisotropy();

    // ******** Compare Function ********
    samplerblock->mCompareFunction = getCompareFunctionFromIndex(samplernode->getCompareFunction());

    // ******** Min LOD ********
    samplerblock->mMinLod = samplernode->getMinLod();

    // ******** Max LOD ********
    samplerblock->mMaxLod = samplernode->getMaxLod();

    // ******** Border colour ********
    Ogre::ColourValue colour;
    colour.r = samplernode->getBorderColourRed() / 255.0f;
    colour.g = samplernode->getBorderColourGreen() / 255.0f;
    colour.b = samplernode->getBorderColourBlue() / 255.0f;
    samplerblock->mBorderColour = colour;
}

//****************************************************************************/
void HlmsBuilder::enrichSamplerNodeGeneric (HlmsNodeSamplerblock* samplernode,
                                            const Ogre::HlmsSamplerblock* samplerblock)
{
    // ******** Enabled ********
    samplernode->setSamplerblockEnabled(true); // default true when loaded

    // ******** Min filter ********
    samplernode->setTextureMinFilter(getIndexFromFilterOption(samplerblock->mMinFilter));

    // ******** Mag filter ********
    samplernode->setTextureMagFilter(getIndexFromFilterOption(samplerblock->mMagFilter));

    // ******** Mip filter ********
    samplernode->setTextureMipFilter(getIndexFromFilterOption(samplerblock->mMipFilter));

    // ******** Texture addressing mode U ********
    samplernode->setTextureAddressingModeU(getIndexFromTAM(samplerblock->mU));

    // ******** Texture addressing mode V ********
    samplernode->setTextureAddressingModeV(getIndexFromTAM(samplerblock->mV));

    // ******** Texture addressing mode W ********
    samplernode->setTextureAddressingModeW(getIndexFromTAM(samplerblock->mW));

    // ******** Mip LOD Bias ********
    samplernode->setMipLodBias(samplerblock->mMipLodBias);

    // ******** Max Anisotropy ********
    samplernode->setMaxAnisotropy(samplerblock->mMaxAnisotropy);

    // ******** Compare Function ********
    samplernode->setCompareFunction(getIndexFromCompareFunction(samplerblock->mCompareFunction));

    // ******** Min LOD ********
    if (samplerblock->mMinLod < -10000000.0f)
        samplernode->setMinLod(-10000000.0f);
    else
        samplernode->setMinLod(samplerblock->mMinLod);

    // ******** Max LOD ********
    if (samplerblock->mMaxLod > 10000000.0f)
        samplernode->setMaxLod(10000000.0f);
    else
        samplernode->setMaxLod(samplerblock->mMaxLod);

    // ******** Border colour ********
    samplernode->setBorderColourRed(255.0f * samplerblock->mBorderColour.r);
    samplernode->setBorderColourGreen(255.0f * samplerblock->mBorderColour.g);
    samplernode->setBorderColourBlue(255.0f * samplerblock->mBorderColour.b);
}

//****************************************************************************/
void HlmsBuilder::enrichMacroblock(HlmsNodeMacroblock* macronode, Ogre::HlmsMacroblock* macroblock)
{
    macroblock->mScissorTestEnabled = macronode->getScissorTestEnabled();
    macroblock->mDepthCheck = macronode->getDepthCheck();
    macroblock->mDepthWrite = macronode->getDepthWrite();
    macroblock->mDepthFunc = getCompareFunctionFromIndex(macronode->getDepthFunc());
    macroblock->mDepthBiasConstant = macronode->getDepthBiasConstant();
    macroblock->mDepthBiasSlopeScale = macronode->getDepthBiasSlopeScale();
    switch (macronode->getCullMode())
    {
        case 0:
            macroblock->mCullMode = Ogre::CULL_NONE;
        break;
        case 1:
            macroblock->mCullMode = Ogre::CULL_CLOCKWISE;
        break;
        case 2:
            macroblock->mCullMode = Ogre::CULL_ANTICLOCKWISE;
        break;
    }
    switch (macronode->getPolygonMode())
    {
        case 0:
            macroblock->mPolygonMode = Ogre::PM_POINTS;
        break;
        case 1:
            macroblock->mPolygonMode = Ogre::PM_WIREFRAME;
        break;
        case 2:
            macroblock->mPolygonMode = Ogre::PM_SOLID;
        break;
    }
}

//****************************************************************************/
void HlmsBuilder::enrichBlendblock(HlmsNodeBlendblock* blendnode, Ogre::HlmsBlendblock* blendblock)
{
    blendblock->mAlphaToCoverageEnabled = blendnode->getAlphaToCoverageEnabled();
    switch (blendnode->getBlendChannelMask())
    {
        case 0:
            blendblock->mBlendChannelMask = Ogre::HlmsBlendblock::BlendChannelRed;
        break;
        case 1:
            blendblock->mBlendChannelMask = Ogre::HlmsBlendblock::BlendChannelGreen;
        break;
        case 2:
            blendblock->mBlendChannelMask = Ogre::HlmsBlendblock::BlendChannelBlue;
        break;
        case 3:
            blendblock->mBlendChannelMask = Ogre::HlmsBlendblock::BlendChannelAlpha;
        break;
        case 4:
            blendblock->mBlendChannelMask = Ogre::HlmsBlendblock::BlendChannelAll;
        break;
    }
    blendblock->mIsTransparent = blendnode->getTransparent();
    blendblock->mSeparateBlend = blendnode->getSeparateBlend();
    blendblock->mSourceBlendFactor = getSceneBlendFactorFromIndex(blendnode->getSourceBlendFactor());
    blendblock->mDestBlendFactor = getSceneBlendFactorFromIndex(blendnode->getDestBlendFactor());
    blendblock->mSourceBlendFactorAlpha = getSceneBlendFactorFromIndex(blendnode->getSourceBlendFactorAlpha());
    blendblock->mDestBlendFactorAlpha = getSceneBlendFactorFromIndex(blendnode->getDestBlendFactorAlpha());
    blendblock->mBlendOperation = getSceneBlendOperationFromIndex(blendnode->getBlendOperation());
    blendblock->mBlendOperationAlpha = getSceneBlendOperationFromIndex(blendnode->getBlendOperationAlpha());
}

//****************************************************************************/
Ogre::CompareFunction HlmsBuilder::getCompareFunctionFromIndex(unsigned int index)
{
    switch (index)
    {
        case 0:
            return Ogre::CMPF_ALWAYS_FAIL;
        break;
        case 1:
            return Ogre::CMPF_ALWAYS_PASS;
        break;
        case 2:
            return Ogre::CMPF_LESS;
        break;
        case 3:
            return Ogre::CMPF_LESS_EQUAL;
        break;
        case 4:
            return Ogre::CMPF_EQUAL;
        break;
        case 5:
            return Ogre::CMPF_NOT_EQUAL;
        break;
        case 6:
            return Ogre::CMPF_GREATER_EQUAL;
        break;
        case 7:
            return Ogre::CMPF_GREATER;
        break;
        case 8:
            return Ogre::NUM_COMPARE_FUNCTIONS;
        break;
    }
}

//****************************************************************************/
unsigned int HlmsBuilder::getIndexFromCompareFunction(Ogre::CompareFunction compareFunction)
{
    switch(compareFunction)
    {
        case Ogre::CMPF_ALWAYS_FAIL:
            return 0;
        break;
        case Ogre::CMPF_ALWAYS_PASS:
            return 1;
        break;
        case Ogre::CMPF_LESS:
            return 2;
        break;
        case Ogre::CMPF_LESS_EQUAL:
            return 3;
        break;
        case Ogre::CMPF_EQUAL:
            return 4;
        break;
        case Ogre::CMPF_NOT_EQUAL:
            return 5;
        break;
        case Ogre::CMPF_GREATER_EQUAL:
            return 6;
        break;
        case Ogre::CMPF_GREATER:
            return 7;
        break;
        case Ogre::NUM_COMPARE_FUNCTIONS:
            return 8;
        break;
    }
}

//****************************************************************************/
Ogre::SceneBlendFactor HlmsBuilder::getSceneBlendFactorFromIndex(unsigned int index)
{
    switch (index)
    {
        case 0:
            return Ogre::SBF_ONE;
        break;
        case 1:
            return Ogre::SBF_ZERO;
        break;
        case 2:
            return Ogre::SBF_DEST_COLOUR;
        break;
        case 3:
            return Ogre::SBF_SOURCE_COLOUR;
        break;
        case 4:
            return Ogre::SBF_ONE_MINUS_DEST_COLOUR;
        break;
        case 5:
            return Ogre::SBF_ONE_MINUS_SOURCE_COLOUR;
        break;
        case 6:
            return Ogre::SBF_DEST_ALPHA;
        break;
        case 7:
            return Ogre::SBF_SOURCE_ALPHA;
        break;
        case 8:
            return Ogre::SBF_ONE_MINUS_DEST_ALPHA;
        break;
        case 9:
            return Ogre::SBF_ONE_MINUS_SOURCE_ALPHA;
        break;
    }
}

//****************************************************************************/
unsigned int HlmsBuilder::getIndexFromSceneBlendFactor(const Ogre::SceneBlendFactor& sceneBlendFactor)
{
    switch (sceneBlendFactor)
    {
        case Ogre::SBF_ONE:
            return 0;
        break;
        case Ogre::SBF_ZERO:
            return 1;
        break;
        case Ogre::SBF_DEST_COLOUR:
            return 2;
        break;
        case Ogre::SBF_SOURCE_COLOUR:
            return 3;
        break;
        case Ogre::SBF_ONE_MINUS_DEST_COLOUR:
            return 4;
        break;
        case Ogre::SBF_ONE_MINUS_SOURCE_COLOUR:
            return 5;
        break;
        case Ogre::SBF_DEST_ALPHA:
            return 6;
        break;
        case Ogre::SBF_SOURCE_ALPHA:
            return 7;
        break;
        case Ogre::SBF_ONE_MINUS_DEST_ALPHA:
            return 8;
        break;
        case Ogre::SBF_ONE_MINUS_SOURCE_ALPHA:
            return 9;
        break;
    }
}

//****************************************************************************/
Ogre::SceneBlendOperation HlmsBuilder::getSceneBlendOperationFromIndex(unsigned int index)
{
    switch (index)
    {
        case 0:
            return Ogre::SBO_ADD;
        break;
        case 1:
            return Ogre::SBO_SUBTRACT;
        break;
        case 2:
            return Ogre::SBO_REVERSE_SUBTRACT;
        break;
        case 3:
            return Ogre::SBO_MIN;
        break;
        case 4:
            return Ogre::SBO_MAX;
        break;
    }
}

//****************************************************************************/
unsigned int HlmsBuilder::getIndexFromSceneBlendOperation(const Ogre::SceneBlendOperation& sceneBlendOperation)
{
    switch (sceneBlendOperation)
    {
        case Ogre::SBO_ADD:
            return 0;
        break;
        case Ogre::SBO_SUBTRACT:
            return 1;
        break;
        case Ogre::SBO_REVERSE_SUBTRACT:
            return 2;
        break;
        case Ogre::SBO_MIN:
            return 3;
        break;
        case Ogre::SBO_MAX:
            return 4;
        break;
    }
}

//****************************************************************************/
unsigned int HlmsBuilder::getIndexFromTAM (Ogre::TextureAddressingMode textureAddressingMode)
{
    switch (textureAddressingMode)
    {
        case Ogre::TAM_WRAP:
            return 0;
        break;
        case Ogre::TAM_MIRROR:
            return 1;
        break;
        case Ogre::TAM_CLAMP:
            return 2;
        break;
        case Ogre::TAM_BORDER:
            return 3;
        break;
        case Ogre::TAM_UNKNOWN:
            return 0;
        break;
    }
    return 999;
}

//****************************************************************************/
Ogre::TextureAddressingMode HlmsBuilder::getTAMFromIndex (unsigned int index)
{
    switch (index)
    {
        case 0:
            return Ogre::TAM_WRAP;
        break;
        case 1:
            return Ogre::TAM_MIRROR;
        break;
        case 2:
            return Ogre::TAM_CLAMP;
        break;
        case 3:
            return Ogre::TAM_BORDER;
        break;
    }
    return Ogre::TAM_UNKNOWN;
}

//****************************************************************************/
unsigned int HlmsBuilder::getIndexFromFilterOption (Ogre::FilterOptions filterOption)
{
    switch (filterOption)
    {
        case Ogre::FO_NONE:
            return 0;
        break;
        case Ogre::FO_POINT:
            return 1;
        break;
        case Ogre::FO_LINEAR:
            return 2;
        break;
        case Ogre::FO_ANISOTROPIC:
            return 3;
        break;
    }

    return 999;
}

//****************************************************************************/
Ogre::FilterOptions HlmsBuilder::getFilterOptionFromIndex (unsigned int index)
{
    switch (index)
    {
        case 0:
            return Ogre::FO_NONE;
        break;
        case 1:
            return Ogre::FO_POINT;
        break;
        case 2:
            return Ogre::FO_LINEAR;
        break;
        case 3:
            return Ogre::FO_ANISOTROPIC;
        break;
    }
    return Ogre::FO_NONE;
}

//****************************************************************************/
bool HlmsBuilder::isResourceLocationExisting(const Ogre::String& path)
{
    Ogre::ResourceGroupManager::LocationList resourceLocations = Ogre::ResourceGroupManager::getSingletonPtr()->
            getResourceLocationList(Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
    Ogre::ResourceGroupManager::LocationList::iterator it;
    Ogre::ResourceGroupManager::LocationList::iterator itStart = resourceLocations.begin();
    Ogre::ResourceGroupManager::LocationList::iterator itEnd = resourceLocations.end();
    for (it = itStart; it != itEnd; ++it)
    {
        Ogre::ResourceGroupManager::ResourceLocation* location = *it;
        Ogre::String name = location->archive->getName();
        if (name == path)
            return true;
    }
    return false;
}

//****************************************************************************/
void HlmsBuilder::saveAllResourcesLocations(void)
{
    // Also add the resource location to the resources.cfg / resources_d.cfg file (for next startup of the application)
    Ogre::StringVector resourceGroups = Ogre::ResourceGroupManager::getSingletonPtr()->getResourceGroups();
    Ogre::StringVector::iterator itGroup;
    Ogre::StringVector::iterator itGroupStart = resourceGroups.begin();
    Ogre::StringVector::iterator itGroupEnd = resourceGroups.end();
    Ogre::String group;
    Ogre::String resourceName;
    QFile file(getResourcesCfg());
    file.open(QFile::WriteOnly | QFile::Text);
    QTextStream writeFile(&file);

    for (itGroup = itGroupStart; itGroup != itGroupEnd; ++itGroup)
    {
        // Iterate through locations
        group = *itGroup;
        writeFile << "[" << group.c_str() << "]\n";
        Ogre::ResourceGroupManager::LocationList resourceLocations = Ogre::ResourceGroupManager::getSingletonPtr()->
                getResourceLocationList(group);
        Ogre::ResourceGroupManager::LocationList::iterator itLocation;
        Ogre::ResourceGroupManager::LocationList::iterator itLocationStart = resourceLocations.begin();
        Ogre::ResourceGroupManager::LocationList::iterator itLocationEnd = resourceLocations.end();
        for (itLocation = itLocationStart; itLocation != itLocationEnd; ++itLocation)
        {
            Ogre::ResourceGroupManager::ResourceLocation* location = *itLocation;
            resourceName = location->archive->getName();
            writeFile << "FileSystem = " << resourceName.c_str() << "\n";
        }
    }

    // Also add the Hlms settings
    writeFile << HLMS_GROUP;
    writeFile << HLMS_DO_NOT_USE_AS_RESOURCE;
    file.close();
}

