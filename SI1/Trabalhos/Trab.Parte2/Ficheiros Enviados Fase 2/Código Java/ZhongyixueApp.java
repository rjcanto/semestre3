/*
 * ZhongyixueApp.java
 */

package zhongyixueapp;

import org.jdesktop.application.Application;
import org.jdesktop.application.SingleFrameApplication;

import java.awt.* ; //For error messages Frame
import java.sql.ResultSet;


/**
 * The main class of the application.
 */
public class ZhongyixueApp extends SingleFrameApplication {

    protected ZhongyixueDB database ;
    /**
     * At startup create and show the main frame of the application.
     */
    @Override protected void startup() {
        database = new ZhongyixueDB() ;
        show(new ZhongyixueView(this, database));
    }

    /**
     * This method is to initialize the specified window by injecting resources.
     * Windows shown in our application come fully initialized from the GUI
     * builder, so this additional configuration is not needed.
     */
    @Override protected void configureWindow(java.awt.Window root) {
    }

    /**
     * A convenient static getter for the application instance.
     * @return the instance of ZhongyixueApp
     */
    public static ZhongyixueApp getApplication() {
        return Application.getInstance(ZhongyixueApp.class);
    }


    /**
     * Main method launching the application.
     */
    public static void main(String[] args) {
        /*TODO Splash screen*/
        //ResultSet rs = db.findPatient();
        //SplashWindow test = new SplashWindow("resources\\chinese-dragon.gif",new Frame());
        launch(ZhongyixueApp.class, args);
        
    }
}
