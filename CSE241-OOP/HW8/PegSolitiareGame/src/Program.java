
import Peg.PegGame;
import javax.imageio.ImageIO;
import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;


public class Program {


    public  static void main(String arg[]){
        /*
            Create Opening Menu, to choose Peg Board Type
         */

        final JFrame frame = new JFrame();
        JButton submit = new JButton("Submit");
        JRadioButton jButton = new JRadioButton("User");
        try{

            JPanel panel = new JPanel();
            panel.setBounds(300,20,400,150);

            BufferedImage img = ImageIO.read(new File("resources/PegGameType.png"));
            JLabel pic = new JLabel(new ImageIcon(img));
            panel.add(pic);
            frame.add(panel);

        }
        catch (IOException e) {

        }

        final JTextField sizeArea = new JTextField();

        JLabel label1 = new JLabel("Enter the board type ( ex:2 ) :");


        label1.setBounds(50, 20, 200, 30);
        sizeArea.setBounds(50, 50, 150, 30);

        jButton.setBounds(50, 110, 150, 40);


        submit.setBounds(200, 200, 150, 50);
        /* Add Action Listener to Submit Button*/
        submit.addActionListener(new ActionListener() {

            @Override
            public void actionPerformed(ActionEvent e) {
                try {

                    int boardType = Integer.parseInt(sizeArea.getText());
                    if(boardType < 6) {
                        PegGame hg = new PegGame(boardType,frame);

                        }
                    else{
                        throw new Exception();
                    }
                }catch(Exception e1) {
                    JOptionPane.showMessageDialog(frame, "You entered invalid status","warning",
                            JOptionPane.WARNING_MESSAGE);
                }
            }
        });

        /* Add label , button,  textfield*/
        frame.add(label1);
        frame.add(sizeArea);
        frame.add(submit);
        frame.add(jButton);
        /* Set frame size*/
        frame.setSize(730,300);

        frame.setDefaultCloseOperation(frame.EXIT_ON_CLOSE);
        frame.setLayout(null);
        frame.setVisible(true);

    }
}
