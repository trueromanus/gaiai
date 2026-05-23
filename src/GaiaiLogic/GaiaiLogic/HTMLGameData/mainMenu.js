const mainMenu = {
	shutDownMode: 1,
	showShutDownModal: function () {
		const width = windowsContainer.clientWidth;
		const height = windowsContainer.clientHeight;
		const modalWidth = 400;
		const modalHeight = 200;
		const centerWidth = (width / 2) - (modalWidth / 2);
		const centerHeight = (height / 2) - (modalHeight / 2);
		mainMenu.shutDownMode = 1;
		taskBar.visibleBlackWall(true);
		const modalOptions = {
			movable: false,
			sizable: false,
			systemTopMost: true
		};

		const contentModal = templateLoader.getTemplate("ShutDownModal");
		taskBar.createWindow('Shut Down SmartCityOS', centerWidth, centerHeight, modalWidth, modalHeight, modalOptions, () => contentModal);
		taskBar.clickOnSmartButton();
	},
	shutDownAction() {
		switch (mainMenu.shutDownMode) {
			case 1:
				//shutdown
				break;
			case 2:
				//restart
				break;
			case 3:
				//close shift
				break;
		}
	},
	showRunModal: function () {
		const modalWidth = 400;
		const modalHeight = 150;
		const centerWidth = (windowsContainer.clientWidth / 2) - (modalWidth / 2);
		const centerHeight = (windowsContainer.clientHeight / 2) - (modalHeight / 2);
		const modalOptions = {
			movable: true,
			sizable: false,
			systemTopMost: false,
			taskbarNotVisible: true
		};
		const contentModal = templateLoader.getTemplate("RunModal");
		taskBar.createWindow('Run', centerWidth, centerHeight, modalWidth, modalHeight, modalOptions, () => contentModal);
		taskBar.clickOnSmartButton();
	},
	showProgramsMenu: function () {
		const contentMenu = templateLoader.getTemplate("ProgramsPopupMenu");

		taskBar.showPopupMenu({ locatedElement: smartmenu, width: 180 }, () => contentMenu);
	},
	showRssReaderWindow: function () {

	},
	showEmailClientWindow: function () {

	},
	showSmartTrackerWindow: function () {

	},
	showWelcomeWindow: function () {
		const modalWidth = 480;
		const modalHeight = 350;
		const centerWidth = (windowsContainer.clientWidth / 2) - (modalWidth / 2);
		const centerHeight = (windowsContainer.clientHeight / 2) - (modalHeight / 2);
		const modalOptions = {
			movable: true
		};
		const contentModal = templateLoader.getTemplate("WelcomeModal");
		taskBar.createWindow('Welcome', centerWidth, centerHeight, modalWidth, modalHeight, modalOptions, () => translator.fillTranslations(contentModal));
		taskBar.clickOnSmartButton();
	}
};