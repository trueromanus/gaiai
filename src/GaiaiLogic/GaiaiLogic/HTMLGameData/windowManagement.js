function replaceClasses(element, oldClass, newClass) {
	element.classList.remove(oldClass);
	element.classList.add(newClass);
}

const windowManagement = {
	moveX: 0,
	moveY: 0,
	windowMoving: false,
	windowResize: false,
	windowResizeDirection: '',
	originalSizeY: 0,
	originalSizeX: 0,
	movingWindow: null,
	endWindowMoving() {
		windowManagement.windowMoving = false;
		windowManagement.windowResize = false;
		windowManagement.windowResizeDirection = '';
	},
	startWindowMoving(e) {
		const clientX = e.clientX || e.touches[0].clientX;
		const clientY = e.clientY || e.touches[0].clientY;
		const windowPanel = e.target.closest('.window-panel');
		windowManagement.moveX = clientX - windowPanel.offsetLeft; 
		windowManagement.moveY = clientY - windowPanel.offsetTop;
		windowManagement.windowMoving = true;
		windowManagement.movingWindow = windowPanel;
	},
	startWindowHorizontalResize(e) {
		windowManagement.windowResizeDirection = 'horizontal';
		windowManagement.startWindowResize(e);					
	},
	startWindowVerticalResize(e) {
		windowManagement.windowResizeDirection = 'vertical';
		windowManagement.startWindowResize(e);					
	},
	startWindowResize(e) {
		const clientX = e.clientX || e.touches[0].clientX;
		const clientY = e.clientY || e.touches[0].clientY;
		const windowPanel = e.target.closest('.window-panel');
		const contentElement = windowPanel.querySelectorAll('.window-content-finder')[0];
		windowManagement.moveX = clientX - windowPanel.clientLeft; 
		windowManagement.moveY = clientY - windowPanel.clientTop;
		windowManagement.windowResize = true;
		windowManagement.movingWindow = contentElement;
		windowManagement.originalSizeY = parseInt(windowManagement.movingWindow.style.height);
		windowManagement.originalSizeX = parseInt(windowManagement.movingWindow.style.width);
	},
	handleWindowMoving(e) {
		if (!windowManagement.windowMoving && !windowManagement.windowResize) return;
		
		if (windowManagement.windowMoving) {	
			windowManagement.windowMoveHandler(e);
			return;
		}
		if (windowManagement.windowResize) {
			windowManagement.windowResizeHandler(e);
			return;						
		}
	},
	windowResizeHandler(e) {
		const notTouches = !e.touches				

		if (windowManagement.windowResizeDirection === 'vertical') {
			const clientY = e.clientY || notTouches || e.touches[0].clientY;
			let newY = clientY - windowManagement.moveY;
			const newHeight = windowManagement.originalSizeY + newY;
			windowManagement.movingWindow.style.height = newHeight + 'px';
		}
		if (windowManagement.windowResizeDirection === 'horizontal') {
			const clientX = e.clientX || notTouches || e.touches[0].clientX;
			let newX = clientX - windowManagement.moveX;
			const newWidth = windowManagement.originalSizeX + newX;
			windowManagement.movingWindow.style.width = newWidth + 'px';
		}
	},
	windowMoveHandler(e) {
		const notTouches = !e.touches
		const clientX = e.clientX || notTouches || e.touches[0].clientX; 
		const clientY = e.clientY || notTouches || e.touches[0].clientY;
		let newX = clientX - windowManagement.moveX;
		let newY = clientY - windowManagement.moveY;
		const currentPositionX = parseInt(windowManagement.movingWindow.style.left);
		const currentPositionY = parseInt(windowManagement.movingWindow.style.top);
		const rightLimit = windowsContainer.offsetWidth - windowManagement.movingWindow.offsetWidth;
		const bottomLimit = windowsContainer.offsetHeight - windowManagement.movingWindow.offsetHeight;
		
		const isLeftNoLimit = newX < 0 && currentPositionX > 0;
		const isRightNoLimit = newX > rightLimit && currentPositionX < rightLimit;
		if (isLeftNoLimit || isRightNoLimit || (newX >= 0 && newX <= rightLimit)) {
			if (newX < 0) newX = 0;
			if (newX > rightLimit) newX = rightLimit;
			
			windowManagement.movingWindow.style.left = newX + 'px';
		}
		
		const isTopNoLimit = newY < 0 && currentPositionY > 0;
		const isBottomNoLimit = newY > bottomLimit && currentPositionY < bottomLimit;
		if (isTopNoLimit || isBottomNoLimit || (newY >= 0 && newY <= bottomLimit)) {
			if (newY < 0) newY = 0;
			if (newY > bottomLimit) newY = bottomLimit;
			
			windowManagement.movingWindow.style.top = newY + 'px';
		}					
	},
	initializeWindowManagement() {
		window.addEventListener('mouseup', windowManagement.endWindowMoving, false); 
		window.addEventListener('touchend', windowManagement.endWindowMoving, false);

		windowsContainer.addEventListener('mousemove', windowManagement.handleWindowMoving, false); 
		windowsContainer.addEventListener('touchmove', windowManagement.handleWindowMoving, false);
	}
}
windowManagement.initializeWindowManagement();

const taskBar = {
	smartButtonClicked: false,
	soundEnabled: true,
	root: null,
	timeFormat: 'HH:MM',
	countWindows: 0,
	windowCounter: 0,
	activatedWindow: null,
	countPopups: 0,
	windows: {},
	clickOnSmartButton: function () {
		if (taskBar.smartButtonClicked) {
			taskBar.smartButtonClicked = false;
			replaceClasses(taskBar.root, "button-pressed-panel", "button-idle-panel");
			smartmenu.style.display = 'none';
		} else {
			taskBar.smartButtonClicked = true;
			replaceClasses(taskBar.root, "button-idle-panel", "button-pressed-panel");
			smartmenu.style.display = 'block';
		}
	},
	registerHandlers: function () {
		taskBar.root = document.getElementById('smart-button-root');
		taskBar.root.addEventListener('click', taskBar.clickOnSmartButton);

		popupMenusContainer.addEventListener('click', (e) => taskBar.closePopupMenu());
	},
	visibleBlackWall: function (visible) {
		blackWall.style.display = visible ? 'block' : 'none';
	},
	createWindow: function (title, x, y, width, height, options, contentCallback) {
		const windowTemplate = templateLoader.getTemplate("WindowModal");

		taskBar.countWindows++;
		taskBar.windowCounter++;
		const systemTopMost = options && options.systemTopMost;
		const taskbarNotVisible = options && options.taskbarNotVisible;
		const zIndex = (systemTopMost ? 400 : 10) + taskBar.countWindows;
		const windowTemplateContent = windowTemplate
			.replaceAll('{{positionY}}', y)
			.replaceAll('{{positionX}}', x)
			.replaceAll('{{title}}', title)
			.replaceAll('{{width}}', width)
			.replaceAll('{{height}}', height)
			.replaceAll('{{windowContent}}', contentCallback())
			.replaceAll('{{windowindex}}', taskBar.windowCounter)
			.replaceAll('{{zindex}}', zIndex + taskBar.countWindows);
		windowsContainer.append(windowTemplateContent);
		const newlyCreatedElement = document.getElementById('window' + taskBar.windowCounter);
		taskBar.windows[taskBar.windowCounter] = newlyCreatedElement;

		const windowIndex = taskBar.windowCounter;
		newlyCreatedElement.addEventListener('mousedown', () => taskBar.activateWindow(windowIndex), false);

		// handle window moving
		if (!options || options.movable) {
			const windowHeader = newlyCreatedElement.querySelector('.window-header-finder');
			windowHeader.addEventListener('mousedown', windowManagement.startWindowMoving, false);
			windowHeader.addEventListener('touchstart', windowManagement.startWindowMoving, false);
		}

		// handle window resize
		if (!options || options.sizable) {
			const horizontalResizer = newlyCreatedElement.querySelector('.horizontal-window-resizer');
			horizontalResizer.addEventListener('mousedown', windowManagement.startWindowVerticalResize, false);
			horizontalResizer.addEventListener('touchstart', windowManagement.startWindowVerticalResize, false);
			const verticalResizer = newlyCreatedElement.querySelector('.vertical-window-resizer');
			verticalResizer.addEventListener('mousedown', windowManagement.startWindowHorizontalResize, false);
			verticalResizer.addEventListener('touchstart', windowManagement.startWindowHorizontalResize, false);
		}

		if (!systemTopMost && !taskbarNotVisible) {
			const buttonTemplate = templateLoader.getTemplate("ButtonTaskbar");
			taskBarButtonContainer.append(buttonTemplate.replaceAll('{{title}}', title).replaceAll('{{windowindex}}', windowIndex));
			taskBarButtonContainer.xcall('createWindow', windowIndex);
		}

		taskBar.activateWindow(taskBar.windowCounter);
	},
	closeWindow: function (windowIndex) {
		const windowElement = taskBar.windows[windowIndex];
		windowsContainer.removeChild(windowElement);
		delete taskBar.windows[windowIndex];

		// active first window if any from it opened
		const keys = Object.keys(taskBar.windows);
		if (keys.length) {
			const newActiveWindow = keys[keys.length - 1];
			taskBar.activateWindow(parseInt(newActiveWindow));
		}

		if (blackWall.style.display !== 'none') taskBar.visibleBlackWall(false);

		taskBarButtonContainer.xcall('closeWindow', windowIndex);
	},
	deactivateWindow() {
		if (!taskBar.activatedWindow) return;

		const currentSelectedItems = document.querySelectorAll('.window-active-header');
		if (currentSelectedItems.length) {
			currentSelected = currentSelectedItems[0]
			replaceClasses(currentSelected, "window-active-header", "window-notactive-header");
		}

		taskBarButtonContainer.xcall('deactivateWindow', taskBar.activatedWindow);
	},
	activateWindow: function (windowIndex) {
		if (taskBar.activatedWindow !== windowIndex) taskBar.deactivateWindow();

		const activableWindow = taskBar.windows[windowIndex];

		const isShowedSystemModal = blackWall.style.display !== 'none';

		if (!isShowedSystemModal && taskBar.windowCounter > 1 && activableWindow.style.zIndex !== taskBar.windowCounter + 10) {
			const lastCounter = taskBar.windowCounter + 10;
			const keys = Object.keys(taskBar.windows);
			for (const key of keys) {
				const window = taskBar.windows[key];
				if (window.style.zIndex > activableWindow.style.zIndex) window.style.zIndex -= 1;
				if (window.style.zIndex === lastCounter) window.style.zIndex -= 1;
			}
			activableWindow.style.zIndex = 10 + taskBar.windowCounter;
		}

		const header = activableWindow.querySelector('.window-header-finder');
		replaceClasses(header, "window-notactive-header", "window-active-header");

		taskBar.activatedWindow = windowIndex;

		taskBarButtonContainer.xcall('activateWindow', windowIndex);
	},
	showPopupMenu: function (options, contentCallback) {
		let left = 0;
		let top = 0;
		const width = options.width || 150;
		if (options.locatedElement) {
			var rect = options.locatedElement.getBoundingClientRect();
			left = rect.right;
			top = rect.top;
		} else {
			left = options.left;
			top = options.top;
		}

		if (options.offsetLeft) left += options.offsetLeft
		if (options.offsetTop) top += options.offsetTop

		taskBar.countPopups++;
		const zIndex = 500;
		const popupMenuTemplate = templateLoader.getTemplate("PopupMenu");
		const menuTemplateContent = popupMenuTemplate
			.replaceAll('{{width}}', width)
			.replaceAll('{{left}}', left)
			.replaceAll('{{top}}', top)
			.replaceAll('{{content}}', contentCallback())
			.replaceAll('{{popupindex}}', taskBar.countPopups)
			.replaceAll('{{zindex}}', zIndex + taskBar.countPopups);

		popupMenusContainer.append(menuTemplateContent);
		popupMenusContainer.style.display = "block";
	},
	closePopupMenu: function () {
		taskBar.countPopups -= 1;
		popupMenusContainer.style.display = "none";
		popupMenusContainer.innerHTML = "";
	}
};
taskBar.registerHandlers();
