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
        mainMenu.welcomePage = 1;
        taskBar.createWindow(
            'Welcome',
            centerWidth,
            centerHeight,
            modalWidth,
            modalHeight,
            modalOptions,
            () => translator.fillTranslations(contentModal),
            (element, windowIndex) => {
                const model = {
                    welcomePage: 1,
                    welcomePageMaximum: 2,
                    root: element,
                    nextPage: function () {
                        if (model.welcomePage === model.welcomePageMaximum) return;

                        model.swapPages(model.welcomePage + 1);
                    },
                    previousPage: function () {
                        if (model.welcomePage === 1) return;

                        model.swapPages(model.welcomePage - 1);
                    },
                    swapPages: function (newPageIndex) {
                        const oldPageIndex = model.welcomePage;
                        model.welcomePage = newPageIndex;
                        const oldPage = element.querySelectorAll('.welcomepage' + oldPageIndex)[0];
                        const newPage = element.querySelectorAll('.welcomepage' + model.welcomePage)[0];
                        oldPage.style.display = 'none';
                        newPage.style.display = 'block';
                    }
                }

                return model;
            }
        );
        taskBar.clickOnSmartButton();
    }
};