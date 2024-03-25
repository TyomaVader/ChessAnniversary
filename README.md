# ChessDev

Developed with Unreal Engine 5

## Network architecture

![image1](https://github.com/TyomaVader/ChessAnniversary/assets/55053620/b7d94030-d40c-45c0-a044-675ee1a08e09)

### ABP_ClassicGameMode 
Returns the "best" playerstart from which this player will appear.The default implementation looks for a random unoccupied spot
@param Player - this is the controller for which we choose playerstart. Returns the action selected to start the player (usually PlayerStart)
AGameModeBase::ChoosePlayerStart - function defining the point of appearance of the client's camera

#### Fields:
 - DefaultSceneRoot - this is the root component of the scene. It is used to initialize and control the game scene. It is usually the starting component for placing other components and actors in the game world.
 - SpawnPoints is a map of player spawn points. Each spawn point is associated with a unique integer identifier. This allows you to select a spawn point for each player depending on certain conditions or game rules.
 - CurrentTurn - current turn in the game. This field is used to track the order of player moves or other game events that depend on the current turn.
 - Engine - a reference to a chess engine object. It can be an external module or a system responsible for the logic of the chess game. The AChessEngine class is supposed to be the class that handles all calculations and checks of chess rules.

#### Methods:
 - ChoosePlayerStart - this function selects the best point for the player to appear. It usually looks for a random unoccupied spot, or may implement other logic for choosing a start point for a player.
 - InitSpawnPoints - this function initializes the player spawn points. It probably sets initial values for SpawnPoints according to game rules or other parameters.

### ABP_ClassicGameState 
This class represents the game state for a classic game. It contains fields that store information about the current game state and its components.

#### Fields:
 - DefaultSceneRoot - this is the root component of the scene. It is used to control the game scene and store information about the current state of the game world. It is typically used to initialize and manage other components and actors in the game world.

### ABP_ClassicHUD 
This class represents the user interface (HUD) for a classic game. It contains the functions and fields needed to display and control the game's user interface.

#### Functions:
 - ToggleWidget - this function allows you to toggle the visibility of the target widget. If the widget is displayed, it will be hidden, and vice versa.
 - FocusWidget - this function sets the focus on the active widget, allowing interaction with it via the keyboard or other control devices.

#### Fields: 
 - DefaultSceneRoot - the scene root component used to control the location and size of the UI.
 - WidgetList - An array of widgets that can be displayed on the HUD screen. This array contains all available widgets for display.
 - ActiveWidget - the active widget that is currently displayed on the HUD screen and that the user can interact with
 - WB_PromotionWidget - a specific widget for displaying the promotion window. This widget is used to show possible promotion options in a classic game.

### ABP_ClassicPlayerController
This class represents the player controller for the classic game. It is responsible for controlling the player's actions in the game world.

#### Class fields:
 - isMyTurn - a variable that determines whether the current player's turn is a turn. It is used to control the order of player's turns.
madeSelection - a variable indicating whether a choice has been made by the player. It is used to track the state of the player's selection.
 - Selector - a pointer to the tile selection actor. Used to determine the tile selected by the player.
 - SelectedTile - coordinates of the tile selected by the player. Used to define the target tile of the action.
 - PlayerID - player identifier. Used to identify a specific player in the game.
 - isFirstTileSelection - variable indicating whether the player's selection is the first one for this turn.
 - fromTile - coordinates of the initial tile for the player's action. It is used to determine the starting point of the move.
 - toTile - coordinates of the final tile for the player's action. Used to define the end point of the move.
 - PlayerHUD - pointer to the player's HUD. Used to display information and interact with the player's HUD.
 - CheckMoveToTile - coordinates of the tile to which the player is going to move. Used to check if the move is possible.
 - CheckMoveFromTile - coordinates of the tile from which the player is going to move. It is used to check if the move is possible.
 - FigureType - type of the figure the player is playing. It is used to determine the possible actions of the figure.
 - GameMode - pointer to the game mode. It is used to interact with the game logic and change game parameters.

#### Class functions:
 - SetMyTurn - sets the player's current turn.
 - SelectTile - function of tile selection by the player. It is used to handle the selection of a tile on the playing field.

#### Other fields:
 - OnTurnChange - delegate called when the player's turn changes. Used to notify other objects of a turn change.

### ABP_ClassicPlayerState 
This class represents the player state for a classic game. It contains information about the current state of the player and his actions.

#### Fields:
 - DefaultSceneRoot - the root component of the scene. It is used to control the game scene and store information about the current state of the player.
 - FromTile - coordinates of the initial tile for the player's action. Used to define the starting point of the move.
 - ToTile - coordinates of the final tile for the player's action. Used to define the end point of the move.

#### Functions:
 - SetFromTile - sets the initial tile for the player action.
 - ABP_MainMenuPlayerController - this class represents the player controller for the main menu of the game. It is responsible for controlling player actions in the main menu.


## Quest System

![QuestSystem2](https://github.com/TyomaVader/ChessAnniversary/assets/55053620/d16f18ab-8de2-466d-b20c-5567a09c520c)

### UTrigger
This class represents a trigger in the game. The trigger can be activated, which will trigger a specific action or event.

#### Class fields:
 - OnTriggerActivated - a dynamic delegate that is called when the trigger is activated. Subscribed functions can be notified when a trigger is activated.

#### Class functions:
- ActivateTrigger - activates the trigger by calling the OnTriggerActivated event.

### UQuestStep
This class represents a job step in the game. Each task step has a description, progress, and an associated trigger that is activated to complete that step.

#### Class fields:
 - StepDescription - A description of this job step. Contains information about what needs to be done to complete the step.
 - StepProgress - the progress of this job step. Usually from 0 to StepProgressTotal, where 0 is the initial state and StepProgressTotal is the completed step.
 - StepProgressTotal - The total progress that must be made to complete this step of the job.
 - StepTriggerId - The ID of the trigger associated with this job step.
 - StepTrigger - allows you to update the progress of the step.

#### Class Events:
 - OnStepProgressUpdated - a dynamic event that is triggered when the progress of this job step is updated.

#### Class Functions:
 - Init - initializes the given job step based on the FQuestStepStruct structure and an array of triggers.
 - GetQuestStepStruct - returns the FQuestStepStruct structure containing information about the current state of the job step.
 - BindToTrigger - binds the given job step to the specified trigger to update progress when the trigger is activated.
 - UpdateProgress - updates the progress of the given job step when the trigger is activated.

### UQuest
The class represents a task in the game, which can consist of several steps. Each job has a title, description, list of steps, current progress, and overall progress of execution. The class also contains delegates to update the progress of a job and the progress of a job step.

#### Class fields:
 - QuestName - the name of this job.
 - QuestDescription - description of the quest, contains information about what you need to do to complete it.
 - QuestSteps - an array of task steps that must be performed to complete this task.
 - Progress - current progress of the task completion.
 - ProgressTotal - total progress of the task completion. This value is defined according to the number of steps of the task.

#### Class functions:
 - UQuest - constructor of the UQuest class.
 - Init - initializes the job using the FQuestStruct structure and an array of triggers.
 - GetQuestStruct - returns the FQuestStruct structure containing information about the job.
 - UpdateProgress - updates the progress of the job when the step is completed.

#### Class delegates:
 - OnQuestProgressUpdated - delegate called when the progress of the job is updated. Subscribed functions can be notified when the job progress changes.
 - OnQuestStepProgressUpdated - a delegate called when the progress of a job step is updated. Subscribed functions can be notified when the progress of a step has changed.

### UQuestManager
This class represents the job manager in the game. It is responsible for managing active and completed jobs.

#### Class fields:
 - Quests - A list of all quests managed by this manager.
 
#### Class functions:
 - Save - Saves the state of all quests to a JSON format file.
 - Load - loads the state of quests from JSON file.
 - AddQuest - adds a new task to the list of active tasks.
 - QuestProgressUpdateNotify - updates the job state and notifies about changes.
 - QuestStepProgressUpdateNotify - updates the job step state and notifies of changes.

#### Class Events:
 - OnQuestNotification - A multi-event that is called when the progress of a job or job step is updated. Allows you to notify other components of changes.

### FQuestStepStruct
This structure represents the data of a single job step in a data table. It contains the step description, the current progress of the step, the overall progress of the step, and the trigger ID associated with the step.

#### Structure fields:
 - StepDescription - A description of this job step. It contains information about what needs to be done to complete this step.
 - StepProgress - the current progress of this job step. The value increases when certain actions are performed or certain conditions are reached.
 - StepProgressTotal - the total progress of this task step. Represents the target progress value that must be achieved to complete the step.
 - StepTriggerId - The ID of the trigger associated with this job step. When the trigger is activated, it can affect the progress of this step.

### FQuestStruct
This structure represents the job data in the data table. It contains the job name, job description, a list of job steps, and the current progress of the job.

#### Structure fields:
 - QuestName - the name of this quest. Unique identifier by which you can identify the task.
 - QuestDescription - description of this task. It contains information about what you need to do to fulfill the task.
 - QuestSteps - an array of FQuestStepStruct structures representing the steps of this task. Each element of the array contains information about a separate step of the task.
 - Progress - current progress of the given task. The value increases when the steps of the quest are completed or certain conditions are reached.

## Quest Parser

### UReadWriteFile
This class provides two functions for working with files.

#### Class functions:
 - ReadStringFromFile - reads the contents of a file with the specified name and returns it as a string. 
 - WriteStringToFile - writes the specified string to the file with the specified name. 

### UReadWriteJson
This class provides four functions to work with JSON files and the FQuestStruct structure.

#### Class functions:
 - ReadStructFromJson - reads the contents of a JSON file with the specified path and fills the passed FQuestStruct structure with data from the file.
 - WriteStructToJson - writes the FQuestStruct structure to the JSON file with the specified path.
 - ReadJson - reads the contents of the JSON file and returns a pointer to an FJsonObject that represents the contents of the file.
 - WriteJson - writes an FJsonObject to a JSON file at the specified path and returns a string with the contents of the JSON file.


