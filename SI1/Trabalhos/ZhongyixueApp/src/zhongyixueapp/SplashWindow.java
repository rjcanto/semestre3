/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package zhongyixueapp;

import java.awt.* ;
import java.awt.event.* ;
import javax.swing.* ;
/**
 *
 * @author Canto
 */
class SplashWindow extends JWindow
{
    public SplashWindow(String filename, Frame f)
    {
        super(f);
        JLabel l = new JLabel(new ImageIcon(filename));
        getContentPane().add(l, BorderLayout.CENTER);
        pack();
        Dimension screenSize =
          Toolkit.getDefaultToolkit().getScreenSize();
        Dimension labelSize = l.getPreferredSize();
        setLocation(screenSize.width/2 - (labelSize.width/2),
                    screenSize.height/2 - (labelSize.height/2));
        addMouseListener(new MouseAdapter()
            {
                public void mousePressed(MouseEvent e)
                {
                    setVisible(false);
                    dispose();
                }
            });
        setVisible(true);
    }
}

