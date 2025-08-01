using GaiaiLogic.Interactive;

namespace GaiaiLogicTests {

    public class GameTrafficLightUnitTests {

        [Fact]
        public void Constructor_Completed_Default () {

            // arrange
            // act
            var trafficLight = new GameTrafficLight ( "arg1", new List<string> () );

            //assert
            Assert.Equal ( "arg1", trafficLight.Title );
            Assert.True ( trafficLight.Correct );
            Assert.True ( trafficLight.CurrentState == trafficLight.CorrectState );
        }

        [Fact]
        public void ChangeState_Completed_Case1 () {

            // arrange
            var trafficLight = new GameTrafficLight ( "arg1", new List<string> () );

            // act
            trafficLight.ChangeState ( 10, 10, 10 );

            //assert
            Assert.Equal ( new ColorTimes ( 10, 10, 10 ), trafficLight.CurrentState );
            Assert.False ( trafficLight.Correct );
        }

        [Fact]
        public void ParseContent_Completed_Case1 () {

            // arrange
            var trafficLight = new GameTrafficLight ( "arg1", new List<string> () );

            // act
            trafficLight.ParseContent (
                """
                green 10
                red 5
                yellow 8
                """
            );

            //assert
            Assert.Equal ( new ColorTimes ( 10, 8, 5 ), trafficLight.CurrentState );
        }

        [Fact]
        public void ParseContent_Completed_Case2 () {

            // arrange
            var trafficLight = new GameTrafficLight ( "arg1", new List<string> () );

            // act
            trafficLight.ParseContent (
                """
                green10
                red   3   
                yellow       52             
                """
            );

            //assert
            Assert.Equal ( new ColorTimes ( 10, 52, 3 ), trafficLight.CurrentState );
        }

        [Fact]
        public void ParseContent_Completed_Case3 () {

            // arrange
            var trafficLight = new GameTrafficLight ( "arg1", new List<string> () );

            // act
            trafficLight.ParseContent (
                """
                red   3   
                yellow       52             
                """
            );

            //assert
            Assert.Equal ( new ColorTimes ( 0, 52, 3 ), trafficLight.CurrentState );
        }

        [Fact]
        public void ParseContent_Completed_Case4 () {

            // arrange
            var trafficLight = new GameTrafficLight ( "arg1", new List<string> () );

            // act
            trafficLight.ParseContent (
                """
                lala 3
                blabla 52
                """
            );

            //assert
            Assert.Equal ( new ColorTimes ( 0, 0, 0 ), trafficLight.CurrentState );
        }

    }

}
