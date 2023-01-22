package Peg;

import javax.swing.*;
import java.awt.*;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Objects;
import java.util.Scanner;

public class PegGame implements  IPegGameEngine , MouseListener , Cloneable {
    private int flag =1;

    private RoundedButton first;
    private  RoundedButton last = null;
    private JFrame _mainFrame;
    private MenuButton _btnUndo,_btnSave, _btnLoad, _btnReset, _btnClone, _btnPlayAuto,_btnPlayAutoAll;
    private JTextField _txtFileName;
    private JLabel _lblFile , _lblscore, _lblscoreShow;
    private JPanel _pnl, _pnlBoard;
    private String _gameType;
    private RoundedButton[][] roundedButtons; /* Store Rounded Buttons(Board Buttons)*/

    private GridBagLayout layout; /* Grid Bag Layout for menu Button*/
    private int _boardType;
    private int _boardSize;
    private Integer _score =0;
    /* Used for previous board status to Undo method*/
    private int firstRow,firstCol;
    private  int lastRow, lastCol;

    /**
     * Peg game Default Constructor
     */
    public PegGame(){};

    /**
     * Create Peg game with desired board Type.
     * @param boardType Board Type
     * @param menuFrame Menu Frame to be closed.
     */
    public PegGame(int boardType,final JFrame menuFrame){
        _boardType = boardType;
        _boardSize =0;
        UIManager.getLookAndFeelDefaults();
        menuFrame.setVisible(false);
        createBoard();
        createMainMenu();
        fillBoard();
        start();
    }

    /**
     * Cell for each Peg BoARD element
     */
    private  class Cell{
        int row, col;
        PegType pegType;

    }

    /* Store the board*/
    private ArrayList<ArrayList<PegType>> board;
    private ArrayList<ArrayList<PegType>> _prevBoard;


    /**
     * Overriden hashCode method
     * @return Object's hash code.
     */
    @Override
    public int hashCode() {
        return Objects.hash(board);
    }


    @Override
    public void createMainMenu() {

        _mainFrame = new JFrame(); // Create Main Frame
        /* Create  MenuButton*/
        _btnUndo = new MenuButton("Undo");
        _btnLoad = new MenuButton("Load");
        _btnSave = new MenuButton("Save");
        _btnReset = new MenuButton("Reset");
        _btnClone = new MenuButton("Clone");
        _lblFile = new JLabel("Enter The File Name");
        _txtFileName = new JTextField(".txt",15);
        _btnPlayAuto = new MenuButton("Auto Move");
        _btnPlayAutoAll = new MenuButton("Auto Play til End");
        _lblscoreShow = new JLabel(_score.toString());
        _lblscore = new JLabel("Score");




        _pnl = new JPanel(); /* Create Panel*/

        /* Board panel*/
        _pnlBoard = new JPanel(new GridBagLayout());
        _pnlBoard.setBounds(20,50,500,500);


        _pnl.setLayout(new GridBagLayout());



        _pnl.setBounds(600,100,150,200);


        /* Grid Baglyout stores the main button*/
        layout = new GridBagLayout();
        _pnl.setLayout(layout);

        GridBagConstraints gbc = new GridBagConstraints();

        // Put constraints on different buttons

        gbc.fill = GridBagConstraints.HORIZONTAL;
        gbc.gridx = 0;
        gbc.gridy = 2;
        _pnl.add(_btnSave, gbc);

        gbc.gridx = 1;
        gbc.gridy = 2;
        _pnl.add(_btnLoad, gbc);

        gbc.gridx = 0;
        gbc.gridy = 3;
        gbc.fill = GridBagConstraints.HORIZONTAL;
        gbc.gridwidth = 2;
        _pnl.add(_btnUndo, gbc);



        gbc.gridx = 0;
        gbc.gridy = 3;
        gbc.fill = GridBagConstraints.HORIZONTAL;
        gbc.gridwidth = 2;
        _pnl.add(_btnUndo, gbc);

        gbc.gridx = 0;
        gbc.gridy = 4;
        gbc.fill = GridBagConstraints.HORIZONTAL;
        gbc.gridwidth =1;
        _pnl.add(_btnReset, gbc);

        gbc.gridx = 1;
        gbc.gridy = 4;
        gbc.fill = GridBagConstraints.HORIZONTAL;
        _pnl.add(_btnClone, gbc);


        gbc.gridx = 0;
        gbc.gridy = 0;
        gbc.fill = GridBagConstraints.HORIZONTAL;
        gbc.gridwidth = 2;
        _pnl.add(_lblFile, gbc);

        gbc.gridx = 0;
        gbc.gridy = 1;
        gbc.fill = GridBagConstraints.HORIZONTAL;
        gbc.gridwidth = 2;
        _pnl.add(_txtFileName, gbc);

        gbc.gridx = 0;
        gbc.gridy =5;
        gbc.fill = GridBagConstraints.HORIZONTAL;
        gbc.gridwidth =2;
        _pnl.add(_btnPlayAuto,gbc);



        gbc.gridx = 0;
        gbc.gridy =6;
        gbc.fill = GridBagConstraints.HORIZONTAL;
        gbc.gridwidth =2;
        _pnl.add(_btnPlayAutoAll,gbc);


        gbc.gridx = 0;
        gbc.gridy =7;
        gbc.fill = GridBagConstraints.HORIZONTAL;
        gbc.gridwidth =1;
        _pnl.add(_lblscore,gbc);


        gbc.gridx = 1;
        gbc.gridy =7;
        gbc.fill = GridBagConstraints.HORIZONTAL;
        gbc.gridwidth =1;
        _pnl.add(_lblscoreShow,gbc);




        _mainFrame.add(_pnl);
        _mainFrame.add(_pnlBoard);


    }

    @Override
    public void fillBoard() {
        /* Create Board Buttons then fill the button with respect to the board peg type. Then Colorize them*/
        createBoardButtons();
        fillBoardButtons();
    }

    @Override
    public void createBoardButtons() {

        /*Create Board buttons using Grid Bag Layout*/

        GridBagConstraints    boardGbc = new GridBagConstraints();
        boardGbc.weightx =_boardSize; boardGbc.weighty =_boardSize;
        boardGbc.gridwidth =1;
        boardGbc.gridheight =1;

        roundedButtons = new RoundedButton[_boardSize][_boardSize];

        for(int i = 0 ; i < _boardSize ; ++i){

            for(int j = 0 ; j < _boardSize ; ++j) {
                boardGbc.fill = GridBagConstraints.BOTH;
                boardGbc.gridx = j;
                boardGbc.gridy = i;

                RoundedButton rbtn = new RoundedButton();
                roundedButtons[i][j] =  rbtn;

                rbtn.addMouseListener(this);
                rbtn.row = boardGbc.gridy;
                rbtn.column = boardGbc.gridx;
                _pnlBoard.add(rbtn, boardGbc);

            }

        }

    }

    @Override
    public void readPegGame() {
        try{
            int r=0;

            /*Open the file. Read Each line. Then parse the line into 2d String array*/
            File pegFile = new File(_txtFileName.getText());
            Scanner scanner = new Scanner(pegFile);
            String types[][] = new String[1][1];
            while (scanner.hasNextLine()){
                if(r == 0) {
                    _boardSize = Integer.parseInt(scanner.nextLine());
                    _boardType = Integer.parseInt(scanner.nextLine());
                    types = new String[_boardSize+1][_boardSize];
                }

                String line = scanner.nextLine();
                types[r] = line.split(" ");
                ++r;
            }

                createBoard();
                /* Set the board element*/
                for(int i =0 ; i< _boardSize ;++i){
                    for(int j =0 ; j<_boardSize; ++j){
                       if(types[i][j].equals("peg")){
                            board.get(i).set(j,PegType.peg);
                       }
                       else if(types[i][j].equals("empty")){
                           board.get(i).set(j,PegType.empty);
                       }
                       else if(types[i][j].equals("space")){
                           board.get(i).set(j,PegType.space);
                       }
                    }
                }
                _pnlBoard.removeAll();
                createBoardButtons();
            fillBoardButtons();
            JOptionPane.showMessageDialog(_mainFrame, "Peg game is readed from file succesfully");
            _score = Integer.parseInt(types[_boardSize][0]);
            _lblscoreShow.setText(_score.toString());
            scanner.close();
        }catch (FileNotFoundException e){
            /* Error message*/
            JOptionPane.showMessageDialog(_mainFrame, "File Could not be opened");

        }


    }

    @Override
    public void savePegGame() {
        /* Save THE pegGME İNTO FİLE*/

        try{
            FileWriter writer = new FileWriter(_txtFileName.getText());
            writer.write(_boardSize+"\n");
            writer.write(_boardType+"\n");
            for(int i =0 ; i< _boardSize ; ++i){
                for (int j =0 ; j<_boardSize; ++j){
                    writer.write(board.get(i).get(j).toString()+" ");
                }
                writer.write("\n");
            }
                writer.write(_score.toString());
            JOptionPane.showMessageDialog(_mainFrame, "Game is saved succesfully");
            writer.close();
        }catch (IOException e){
            JOptionPane.showMessageDialog(_mainFrame, "File Could not be created");
        }


    }


    @Override
    public void reset() {

        _initialScore();
        _lblscoreShow.setText(_score.toString());
        createBoard();
        fillBoardButtons();
    }




    @Override
    public void start() {

        _btnPlayAuto.addMouseListener(this);
        _btnPlayAutoAll.addMouseListener(this);
        _btnUndo.addMouseListener(this);
        _btnSave.addMouseListener(this);
        _btnLoad.addMouseListener(this);
        _btnReset.addMouseListener(this);
        _mainFrame.setBounds(0,0,800,600);
        _mainFrame.setLayout(null);
        _mainFrame.setVisible(true);
    }

    @Override
    public void playAuto() {
        /* Get random move*/
        while (true && !isGameEnded()) {
            firstRow = ranInt();
            firstCol = ranInt();
            lastRow = ranInt();
            lastCol = ranInt();


            if (canMove()) {
                makeMove();
                break;
            }
            else{

            }
        }
        flag =1;
    }

    @Override
    public void playAutoAll(){
        while (!isGameEnded()) {
            playAuto();
        }
        System.out.println("Move is made by computer until the end");
        flag =1;
    }

    @Override
    public void playUser() {
        if (last != null && flag == 1) {

            if (canMove()) {
                makeMove();
                System.out.println("Move is made by user");
            }
        }
    }

    /**
     * Shows initial board score according to board type.
     */
    private void _initialScore() {
        switch (_boardType){
            case 1:
                _score = 36;
                break;
            case 2:
                _score = 44;
                break;
            case 3:
                 _score =38;
                 break;
            case 4:
                _score =32;
                break;
            case 5:
                _score = 42;
                break;
            default:
                break;
        }
    }

    @Override
    public void createBoard() {
        _initialScore();
        this.board = new ArrayList<ArrayList<PegType>>();
        switch (_boardType){

            case 1:
                _boardSize = 7;

                board.add(new ArrayList<>(Arrays.asList(
                        PegType.space,PegType.space,PegType.peg,PegType.peg,PegType.peg,PegType.space,PegType.space)));
                board.add(new ArrayList<>(Arrays.asList(
                        PegType.space,PegType.peg,PegType.peg,PegType.peg,PegType.peg,PegType.peg,PegType.space)));

                board.add(new ArrayList<>(Arrays.asList(
                        PegType.peg,PegType.peg,PegType.peg,PegType.empty,PegType.peg,PegType.peg,PegType.peg)));
                board.add(new ArrayList<>(Arrays.asList(
                        PegType.peg,PegType.peg,PegType.peg,PegType.peg,PegType.peg,PegType.peg,PegType.peg)));
                board.add(new ArrayList<>(Arrays.asList(
                        PegType.peg,PegType.peg,PegType.peg,PegType.peg,PegType.peg,PegType.peg,PegType.peg)));

                board.add(new ArrayList<>(Arrays.asList(
                        PegType.space,PegType.peg,PegType.peg,PegType.peg,PegType.peg,PegType.peg,PegType.space)));
                board.add(new ArrayList<>(Arrays.asList(
                        PegType.space,PegType.space,PegType.peg,PegType.peg,PegType.peg,PegType.space,PegType.space)));


                break;
            case 2:
                _boardSize = 9;

                board.add(new ArrayList<>(Arrays.asList(
                        PegType.space,PegType.space,PegType.space,PegType.peg,PegType.peg,PegType.peg,PegType.space,PegType.space,PegType.space)));
                board.add(new ArrayList<>(Arrays.asList(
                        PegType.space,PegType.space,PegType.space,PegType.peg,PegType.peg,PegType.peg,PegType.space,PegType.space,PegType.space)));
                board.add(new ArrayList<>(Arrays.asList(
                        PegType.space,PegType.space,PegType.space,PegType.peg,PegType.peg,PegType.peg,PegType.space,PegType.space,PegType.space)));

                board.add(new ArrayList<>(Arrays.asList(
                        PegType.peg,PegType.peg,PegType.peg,PegType.peg,PegType.peg,PegType.peg,PegType.peg,PegType.peg,PegType.peg)));
                board.add(new ArrayList<>(Arrays.asList(
                        PegType.peg,PegType.peg,PegType.peg,PegType.peg,PegType.empty,PegType.peg,PegType.peg,PegType.peg,PegType.peg)));
                board.add(new ArrayList<>(Arrays.asList(
                        PegType.peg,PegType.peg,PegType.peg,PegType.peg,PegType.peg,PegType.peg,PegType.peg,PegType.peg,PegType.peg)));

                board.add(new ArrayList<>(Arrays.asList(
                        PegType.space,PegType.space,PegType.space,PegType.peg,PegType.peg,PegType.peg,PegType.space,PegType.space,PegType.space)));
                board.add(new ArrayList<>(Arrays.asList(
                        PegType.space,PegType.space,PegType.space,PegType.peg,PegType.peg,PegType.peg,PegType.space,PegType.space,PegType.space)));
                board.add(new ArrayList<>(Arrays.asList(
                        PegType.space,PegType.space,PegType.space,PegType.peg,PegType.peg,PegType.peg,PegType.space,PegType.space,PegType.space)));

                break;

            case 3:
                _boardSize =8;

                board.add(new ArrayList<>(Arrays.asList(
                        PegType.space,PegType.space,PegType.peg,PegType.peg,PegType.peg,PegType.space,PegType.space,PegType.space)));
                board.add(new ArrayList<>(Arrays.asList(
                        PegType.space,PegType.space,PegType.peg,PegType.peg,PegType.peg,PegType.space,PegType.space,PegType.space)));
                board.add(new ArrayList<>(Arrays.asList(
                        PegType.space,PegType.space,PegType.peg,PegType.peg,PegType.peg,PegType.space,PegType.space,PegType.space)));

                board.add(new ArrayList<>(Arrays.asList(
                        PegType.peg,PegType.peg,PegType.peg,PegType.peg,PegType.peg,PegType.peg,PegType.peg,PegType.peg)));
                board.add(new ArrayList<>(Arrays.asList(
                        PegType.peg,PegType.peg,PegType.peg,PegType.empty,PegType.peg,PegType.peg,PegType.peg,PegType.peg)));
                board.add(new ArrayList<>(Arrays.asList(
                        PegType.peg,PegType.peg,PegType.peg,PegType.peg,PegType.peg,PegType.peg,PegType.peg,PegType.peg)));

                board.add(new ArrayList<>(Arrays.asList(
                        PegType.space,PegType.space,PegType.peg,PegType.peg,PegType.peg,PegType.space,PegType.space,PegType.space)));
                board.add(new ArrayList<>(Arrays.asList(
                        PegType.space,PegType.space,PegType.peg,PegType.peg,PegType.peg,PegType.space,PegType.space,PegType.space)));


                break;
            case 4:
                _boardSize = 7;
                board.add(new ArrayList<>(Arrays.asList(
                        PegType.space,PegType.space,PegType.peg,PegType.peg,PegType.peg,PegType.space,PegType.space)));
                board.add(new ArrayList<>(Arrays.asList(
                        PegType.space,PegType.space,PegType.peg,PegType.peg,PegType.peg,PegType.space,PegType.space)));

                board.add(new ArrayList<>(Arrays.asList(
                        PegType.peg,PegType.peg,PegType.peg,PegType.peg,PegType.peg,PegType.peg,PegType.peg)));
                board.add(new ArrayList<>(Arrays.asList(
                        PegType.peg,PegType.peg,PegType.peg,PegType.empty,PegType.peg,PegType.peg,PegType.peg)));
                board.add(new ArrayList<>(Arrays.asList(
                        PegType.peg,PegType.peg,PegType.peg,PegType.peg,PegType.peg,PegType.peg,PegType.peg)));

                board.add(new ArrayList<>(Arrays.asList(
                        PegType.space,PegType.space,PegType.peg,PegType.peg,PegType.peg,PegType.space,PegType.space)));
                board.add(new ArrayList<>(Arrays.asList(
                        PegType.space,PegType.space,PegType.peg,PegType.peg,PegType.peg,PegType.space,PegType.space)));

                break;
            case 5:
                _boardSize = 9;

                board.add(new ArrayList<>(Arrays.asList(
                        PegType.space,PegType.space,PegType.space,PegType.space,PegType.peg,PegType.space,PegType.space,PegType.space,PegType.space)));
                board.add(new ArrayList<>(Arrays.asList(
                        PegType.space,PegType.space,PegType.space,PegType.peg,PegType.peg,PegType.peg,PegType.space,PegType.space,PegType.space)));
                board.add(new ArrayList<>(Arrays.asList(
                        PegType.space,PegType.space,PegType.peg,PegType.peg,PegType.peg,PegType.peg,PegType.peg,PegType.space,PegType.space)));
                board.add(new ArrayList<>(Arrays.asList(
                        PegType.space,PegType.peg,PegType.peg,PegType.peg,PegType.peg,PegType.peg,PegType.peg,PegType.peg,PegType.space)));

                board.add(new ArrayList<>(Arrays.asList(
                        PegType.peg,PegType.peg,PegType.peg,PegType.peg,PegType.empty,PegType.peg,PegType.peg,PegType.peg,PegType.peg)));

                board.add(new ArrayList<>(Arrays.asList(
                        PegType.space,PegType.peg,PegType.peg,PegType.peg,PegType.peg,PegType.peg,PegType.peg,PegType.peg,PegType.space)));
                board.add(new ArrayList<>(Arrays.asList(
                        PegType.space,PegType.space,PegType.peg,PegType.peg,PegType.peg,PegType.peg,PegType.peg,PegType.space,PegType.space)));
                board.add(new ArrayList<>(Arrays.asList(
                        PegType.space,PegType.space,PegType.space,PegType.peg,PegType.peg,PegType.peg,PegType.space,PegType.space,PegType.space)));
                board.add(new ArrayList<>(Arrays.asList(
                        PegType.space,PegType.space,PegType.space,PegType.space,PegType.peg,PegType.space,PegType.space,PegType.space,PegType.space)));


                break;


            default:
                throw new IllegalStateException("Unexpected value: " + _boardType);
        }


    }

    @Override
    public boolean canMove() {

        boolean status = false;
        boolean flag1 = false;

        /* Get middle peg location*/
        int midRow = (lastRow + firstRow)/2;
        int midCol = (lastCol + firstCol) /2;

        this.flag =1;

        if((firstRow == lastRow && Math.abs(firstCol-lastCol) ==2) ||
                (firstCol == lastCol && Math.abs(firstRow-lastRow) ==2) ){
            flag1 = true;


        }



        if(board.get(lastRow).get(lastCol) == PegType.empty &&
                board.get(midRow).get(midCol) == PegType.peg &&
                board.get(firstRow).get(firstCol) == PegType.peg && flag1){
            status = true;
        }

        return status;
    }

    @Override
    public void makeMove(){

        --_score;

        _lblscoreShow.setText(_score.toString());

        _prevBoard = new ArrayList<>();
        for(int i = 0 ; i < _boardSize ; ++i){
                _prevBoard.add(new ArrayList<>(board.get(i)));
        }

        /* Get middile peg*/
        int midRow = (firstRow+lastRow)/2;
        int midCol = (firstCol+lastCol)/2;

            /* Set the board*/
        board.get(firstRow).set(firstCol,PegType.empty);
        board.get(lastRow).set(lastCol,PegType.peg);
        board.get(midRow).set(midCol,PegType.empty);

        /* Set the color*/
        roundedButtons[firstRow][firstCol].color = Color.lightGray;
        roundedButtons[firstRow][firstCol].repaint();
        roundedButtons[lastRow][lastCol].color = Color.BLACK;
        roundedButtons[lastRow][lastCol].repaint();
        roundedButtons[midRow][midCol].color = Color.lightGray;
        roundedButtons[midRow][midCol].repaint();


        _mainFrame.getToolkit().sync();
    }

    @Override
    public int ranInt() {

        return (int) (Math.random() *_boardSize);
    }

    @Override
    public boolean isGameEnded() {
        int peg_num=0;
        int flag=0;
        for(int i=0;i<_boardSize;++i){
            for(int j=0;j<_boardSize;++j){
                if((board).get(i).get(j)== PegType.peg){
                    ++peg_num;
                    if(j-2>=0 && (board).get(i).get(j-2) == PegType.empty && (board).get(i).get(j-1) == PegType.peg){
                        flag=1;
                    }
                    if(j+2 < _boardSize && (board).get(i).get(j+2) == PegType.empty && (board).get(i).get(j+1) == PegType.peg){
                        flag=1;
                    }
                    if(i-2>=0 && (board).get(i-2).get(j) == PegType.empty && (board).get(i-1).get(j) == PegType.peg){
                        flag=1;
                    }
                    if(i+2<(board).size() && (board).get(i+2).get(j) == PegType.empty && (board).get(i+1).get(j) == PegType.peg){
                        flag=1;
                    }
                    if(flag==1){
                        return false;
                    }
                }
            }
        }
        /* if there is a only one pegs, the game is finished by best score*/
        if(peg_num == 1){
            return true;
        }
        return true;

    }

    @Override
    public void undo() {
        board = _prevBoard;
        fillBoardButtons();
        first = null;
        last = null;
        ++_score;
        flag =1;
        _lblscoreShow.setText(_score.toString());
    }

    @Override
    public void fillBoardButtons() {


        for(int i = 0 ; i< _boardSize ; ++i){
            for(int j = 0 ; j< _boardSize ;++j){
                if(board.get(i).get(j).ordinal() == 0){
                    roundedButtons[i][j].color = Color.BLACK;
                    roundedButtons[i][j].repaint();
                }
                else if(board.get(i).get(j).ordinal() == 1){
                    roundedButtons[i][j].color =  Color.lightGray;
                    roundedButtons[i][j].repaint();

                }
                else{
                    roundedButtons[i][j].color =  Color.WHITE;
                    roundedButtons[i][j].repaint();
                }
            }
        }

    }

    /**
     * Mouse Cliked Events
     * @param e Mouse Event
     */
    @Override
    public void mouseClicked(MouseEvent e) {
        /* to Do*/


    }

    @Override
    public void mousePressed(MouseEvent e) {
        /* If the button is instance of Menu Button, start the event according to Menu Button method*/
        if(e.getComponent() instanceof  MenuButton){
            MenuButton btn = (MenuButton) e.getComponent();
            if(btn.text.compareTo("Auto Move") == 0){
                System.out.println("Auto Move pressed");
                playAuto();
                System.out.println("Move is made by computer");
            }
            else if(btn.text.compareTo("Auto Play til End") == 0){
                System.out.println("Auto Play til End pressed");
                playAutoAll();
            }

            else if(btn.text.compareTo("Undo") == 0){
                System.out.println("Undo Pressed");
                undo();
            }

            else if(btn.text.compareTo("Save") == 0){
                System.out.println("Save Pressed");
                savePegGame();
            }
            else if(btn.text.compareTo("Load") == 0){
                System.out.println("Load Pressed");

                readPegGame();

            }
            else if(btn.text.compareTo("Reset") ==0){   reset();
                System.out.println("Reset Pressed");

            }


        }
    }

    @Override
    public void mouseReleased(MouseEvent e) {





        /* If the event's compomenent is instance of Rounded Button (Peg Solitaire Board Peg)*/
        if(e.getComponent() instanceof  RoundedButton){

            if (flag == 1) {
                first = (RoundedButton) e.getComponent();
                firstRow = first.row;
                firstCol = first.column;
                flag = 0;


            } else {
                last = (RoundedButton) e.getComponent();
                lastRow = last.row;
                lastCol = last.column;
                flag = 1;


            }
            playUser();
        }

    }

    @Override
    public void mouseEntered(MouseEvent e) {
        /* to DO*/

    }

    @Override
    public void mouseExited(MouseEvent e) {
        /* to DO*/

    }

    /* Overriden Clone Method*/
    @Override
    public  PegGame clone() {
        try{

            PegGame clone = (PegGame) super.clone();
            return  clone;

        }
        catch (CloneNotSupportedException e){

            return null;
        }
    }
}
