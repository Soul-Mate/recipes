import javax.swing.*;
import java.awt.*;
import java.awt.geom.Ellipse2D;

public class AlgoFrame extends JFrame {
    private final int canvasW;

    private final int canvasH;

    AlgoFrame(String title, int canvasWeight, int canvasHeight) {
        super(title);
        canvasW = canvasWeight;
        canvasH = canvasHeight;
    }


    public void visible() {
//        AlgoCanvas canvas = new AlgoCanvas();
//        setContentPane(canvas);
//        pack();

        setSize(canvasW, canvasH);
        setResizable(false);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setVisible(true);
    }

    AlgoFrame(String title) {
        this(title, 1024, 768);
    }

    public int getCanvasWeight() {
        return canvasW;
    }

    private int getCanvasHeight() {
        return canvasH;
    }


    private class AlgoCanvas extends JPanel {
        public AlgoCanvas() {
            // 抗锯齿
            super(true);
        }

        @Override
        public void paintComponent(Graphics g) {
            super.paintComponent(g);

            Graphics2D g2d = (Graphics2D) g;

            // 抗锯齿
            RenderingHints hints = new RenderingHints(
                    RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);
            g2d.addRenderingHints(hints);



            // 设置线条粗细
            int strokeWidth = 2;
            AlgoHelper.setStrokeWidth(g2d, 2);

            // 改变颜色状态（swing是基于状态的）
            AlgoHelper.setColor(g2d, Color.GRAY);
            AlgoHelper.fillCircle(g2d, canvasW / 2, canvasH / 2, 200);

            // 设置圆形的颜色
            AlgoHelper.setColor(g2d, Color.RED);
            AlgoHelper.strokeCircle(g2d, canvasW / 2, canvasH / 2, 200);

        }

        @Override
        public Dimension getPreferredSize() {
            return new Dimension(canvasH, canvasW);
        }
    }
}
