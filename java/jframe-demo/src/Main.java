import javax.swing.*;
import java.awt.*;

public class Main {

    public static void main(String[] args) {

        int N = 100;
        int screenWeight = 1080;
        int screenHeight = 1920;

        int R = 20;
        Circle[] circles = new Circle[N];
        for (int i = 0; i < N; i++) {
            int x = (int) (Math.random() * (screenWeight - 2 * R)) + R;
            int y = (int) (Math.random() * (screenHeight - 2 * R)) + R;
            int vx = (int) (Math.random() * 11) - 5;
            int vy = (int) (Math.random() * 11) - 5;
            circles[i] = new Circle(x, y, R, vx, vy);
        }

        EventQueue.invokeLater(() -> {
            CircleCanvas circleCanvas = new CircleCanvas(circles);
            AlgoFrame frame = new AlgoFrame("welcome");
            frame.setContentPane(circleCanvas);
            frame.pack();
            frame.visible();
            new Thread(() -> {
                while (true) {
                    circleCanvas.setCircles(circles);
                    frame.repaint();

                    try {
                        Thread.sleep(20);
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }

                    for(Circle circle : circles)
                        circle.move(0, 0, screenWeight, screenHeight);

                }
            }).start();
        });
    }
}
