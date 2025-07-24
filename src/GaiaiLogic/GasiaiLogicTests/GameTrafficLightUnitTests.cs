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

    }

}
