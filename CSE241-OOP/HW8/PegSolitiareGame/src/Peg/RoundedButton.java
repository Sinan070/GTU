package Peg;

import javax.swing.*;
import java.awt.*;

/**
 *  Rounded button that represent Peg Board. Extends from JButton.
 */
public class RoundedButton extends JButton {
    public  Color color;
    public int row,column;

    /** Rounded Button constructor
     *  Set the dimension, backgraound color etc..
     */
    public RoundedButton(){
        setFocusable(false);
        setBackground(Color.lightGray);
        Dimension size = getPreferredSize();
        size.width = size.height = Math.max(size.width,size.height);
        setPreferredSize(size);
        setContentAreaFilled(false);
    }

    /** Overrided
     *  Paint Component Method to make Button raounded.
     * @param g is a graphics element.
     */
    @Override
    protected void paintComponent(Graphics g) {

        g.setColor(color);
        g.fillOval(0, 0, getSize().width - 1, getSize().height - 1);
        super.paintComponent(g);
    }

    /**
     * Overrided paintBorder method used for draw rounded border.
     * @param g graphics element.
     */
    @Override
    protected void paintBorder(Graphics g) {

        g.setColor(color);
        g.drawOval(0, 0, getSize().width - 1, getSize().height - 1);

        super.paintBorder(g);

    }


}
