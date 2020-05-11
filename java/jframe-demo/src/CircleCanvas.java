import javax.swing.*;
import java.awt.*;

public class CircleCanvas extends JPanel {
    Circle[] circles;

    public CircleCanvas(Circle[] circles) {
        // 抗锯齿
        super(true);
        this.circles = circles;
    }

    public void setCircles(Circle[] circles) {
        this.circles = circles;
    }

    @Override
    public void paintComponent(Graphics g) {
        super.paintComponent(g);

        Graphics2D g2d = (Graphics2D) g;

        // 抗锯齿
        RenderingHints hints = new RenderingHints(
                RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);
        g2d.addRenderingHints(hints);

        AlgoHelper.setStrokeWidth(g2d, 1);
        AlgoHelper.setColor(g2d, Color.RED);
        for (Circle circle: circles) {
            AlgoHelper.strokeCircle(g2d, circle.x, circle.y, circle.getR());
        }
    }
}
