package Peg;

import javax.swing.*;
import java.awt.*;

/**
 *  Menu button sub class extends from JButton
 */
public class MenuButton extends JButton {
    public String text;

    /**
     * Menu Button Constructor
     * @param type menu Button type. etc. Undo,reset...
     */
    MenuButton(String type){
        super(type);
        text =  type;
    }
}
