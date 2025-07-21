using GaiaiLogic;

namespace GaiaiLogicTests {

    public class TriggerHubUnitTests {

        [Fact]
        public void EnableTrigger_Completed_HappyPath () {
            // arrange
            var hub = new TriggersHub ();

            // act
            hub.EnableTrigger ( "test1" );

            // assert
            Assert.True ( hub.TriggerIsEnabled ( "test1" ) );
        }

        [Fact]
        public void EnableTrigger_Completed_AlreadyAdded () {
            // arrange
            var hub = new TriggersHub ();
            hub.EnableTrigger ( "test1" );

            // act
            hub.EnableTrigger ( "test1" );

            // assert
            Assert.True ( hub.TriggerIsEnabled ( "test1" ) );
        }

        [Fact]
        public void DisableTrigger_Completed_HappyPath () {
            // arrange
            var hub = new TriggersHub ();
            hub.EnableTrigger ( "test2" );

            // act
            hub.DisableTrigger ( "test2" );

            // assert
            Assert.False ( hub.TriggerIsEnabled ( "test2" ) );
        }

        [Fact]
        public void DisableTrigger_Completed_NotExists () {
            // arrange
            var hub = new TriggersHub ();

            // act
            hub.DisableTrigger ( "test2" );

            // assert
            Assert.False ( hub.TriggerIsEnabled ( "test2" ) );
        }

    }

}
