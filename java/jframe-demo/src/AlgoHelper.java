import java.awt.*;
import java.awt.geom.Ellipse2D;

public class AlgoHelper {
    AlgoHelper() {
    }

    public static void setStrokeWidth(Graphics2D g2d, int w) {
        g2d.setStroke(new BasicStroke(w, BasicStroke.CAP_ROUND, BasicStroke.JOIN_ROUND));
    }

    public static void strokeCircle(Graphics2D g2d, int x, int y, int r) {
        Ellipse2D circle = new Ellipse2D.Float(x - r, y - r, r * 2, r * 2);
        g2d.draw(circle);
    }


    public static void fillCircle(Graphics2D g2d, int x, int y, int r) {
        Ellipse2D circle = new Ellipse2D.Float(x - r, y - r, r * 2, r * 2);
        g2d.fill(circle);
    }

    public static void setColor(Graphics2D g2d, Color color) {
        g2d.setColor(color);
    }
}
