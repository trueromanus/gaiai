using GaiaiLogic.Translate;

namespace GaiaiLogicTests
{

    public class TranslatorUnitTests
    {

        [Fact]
        public void FillTranslations_Completed_HappyPath()
        {
            // arrange
            var template = "dkflsdkflls dlsdfk lsdkfl lsdfk lkdsf {{trans_001}}";
            var translator = new Translator();
            translator.AddToTranslation("001", "replace");

            // act
            var result = translator.FillTranslations(template);

            // assert
            Assert.Equal("dkflsdkflls dlsdfk lsdkfl lsdfk lkdsf replace", result);
        }

        [Fact]
        public void FillTranslations_Completed_InMiddle()
        {
            // arrange
            var template = "dkflsdkflls dlsdfk{{trans_001}}lsdkfl lsdfk lkdsf";
            var translator = new Translator();
            translator.AddToTranslation("001", "replace");

            // act
            var result = translator.FillTranslations(template);

            // assert
            Assert.Equal("dkflsdkflls dlsdfkreplacelsdkfl lsdfk lkdsf", result);
        }

        [Fact]
        public void FillTranslations_Completed_MultipleSameTranslation()
        {
            // arrange
            var template = "{{trans_001}}dkflsdkflls dlsdfk{{trans_001}}lsdkfl lsdfk lkdsf{{trans_001}}";
            var translator = new Translator();
            translator.AddToTranslation("001", "replace");

            // act
            var result = translator.FillTranslations(template);

            // assert
            Assert.Equal("replacedkflsdkflls dlsdfkreplacelsdkfl lsdfk lkdsfreplace", result);
        }

        [Fact]
        public void FillTranslations_Completed_MultipleDifferentTranslations()
        {
            // arrange
            var template = "{{trans_001}}dkflsdkflls dlsdfk{{trans_002}}lsdkfl lsdfk lkdsf{{trans_003}}";
            var translator = new Translator();
            translator.AddToTranslation("001", "replace1");
            translator.AddToTranslation("002", "replace2");
            translator.AddToTranslation("003", "replace3");

            // act
            var result = translator.FillTranslations(template);

            // assert
            Assert.Equal("replace1dkflsdkflls dlsdfkreplace2lsdkfl lsdfk lkdsfreplace3", result);
        }

    }

}
