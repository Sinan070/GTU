package Peg;

/**
 * Peg Solitaire Engine Interface
 */
public interface IPegGameEngine {
    /**
     * Add Main Menu Buttons the Mouse Listener
     * Set main frame properties.
     */
    void start();

    /**
     * Move automatically once.
     */
    void playAuto();

    /**
     * Move automatically until the game is ended.
     */
    void playAutoAll();

    /**
     * Play by user.
     */
    void playUser();

    /**
     * Create Main Menu properties. Like undo,reset,load .. buttons within GridBag Layout.
     */
    void createMainMenu();

    /**
     * Create Board Button then set the Board button according to the board properties.
     */
    void fillBoard();

    /**
     * Create Board according to Peg Board Choice.
     */
    void createBoard();

    /**
     * Check the move is valid or not.
     * @return move validation
     */
    boolean canMove();

    /**
     * Make Move. Then Set the Peg Button color and change the board.
     */
    void makeMove();

    /**
     * Get random integer value to use random move.
     * @return random integer value.
     */
    int ranInt();

    /**
     * Check the Game is ended or not.
     * @return boolean to represent game status.
     */
    boolean isGameEnded();

    /**
     * Undo the game once.
     */
    void undo();

    /**
     * Fill Board Button according to Board. Then set the Board Button color.
     * Button is rounded button.
     */
    void fillBoardButtons();

    /**
     * Create Board buttons. Board Buttons are rounded button.
     */
    void createBoardButtons();

    /**
     * Read Peg Game from text file.
     */
    void readPegGame();

    /**
     * Save the Peg game to the file.
     */
    void savePegGame();

    /**
     * Reset the Peg Game. Back to initial peg board status.
     */
    void reset();








}
