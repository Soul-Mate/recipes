public class Circle {
    public int x;
    public int y;
    private int r;
    public int velocityX;
    public int velocityY;

    Circle(int x, int y, int r, int velocityX, int velocityY) {
        this.x = x;
        this.y = y;
        this.r = r;
        this.velocityX = velocityX;
        this.velocityY = velocityY;
    }

    public void move(int minX, int minY, int maxX, int maxY) {
        x += velocityX;
        y += velocityY;
        checkCollision(minX, minY, maxX, maxY);
    }

    public int getR() {
        return r;
    }

    private void checkCollision(int minX, int minY, int maxX, int maxY) {
        if (x - r < minX) {
            x = r;
            velocityX = -velocityX;
        }
        if (x + r > maxX) {
            x = maxX - r;
            velocityX = -velocityX;
        }
        if (y - r < minY) {
            y = r;
            velocityY = -velocityY;
        }
        if (y + r > maxY) {
            y = maxY - r;
            velocityY = -velocityY;
        }
    }


    private boolean isCollisionWithCircle(int x1, int y1, int x2, int y2, int r1, int r2) {
        if (Math.sqrt(Math.pow(x1 - x2, 2) + Math.pow(y1 - y2, 2)) <= r1 + r2) {
            return true;
        }
        return false;
    }
}
