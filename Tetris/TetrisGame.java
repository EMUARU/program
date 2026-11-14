import java.util.ArrayList;
import java.util.List;
import java.util.Arrays;
import java.util.Random;
import java.util.Collections;
import java.lang.Math;
import java.awt.geom.*;
import java.awt.image.*;
import javax.imageio.*;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;


class Shape {
    private int[][] matrix;
    private int x;
    private int y;
    private Color color;

    public Shape(int[][] matrix, Color color) {
        this.matrix = matrix;
        this.x = 4;
        this.y = 0;
        this.color = color;
    }

    public int[][] getMatrix() {
        return matrix;
    }

    public int getX() {
        return x;
    }

    public int getY() {
        return y;
    }

    public void moveLeft() {
        x--;
    }

    public void moveRight() {
        x++;
    }

    public void moveDown() {
        y++;
    }

    public void setX(int x) {
        this.x = x;
    }

    public void setY(int y) {
        this.y = y;
    }

    public Color getColor() {
        return color;
    }

    public Shape rotate() {
        int[][] newMatrix = new int[matrix[0].length][matrix.length];
        for (int i = 0; i < matrix.length; i++) {
            for (int j = 0; j < matrix[i].length; j++) {
                newMatrix[j][matrix.length - 1 - i] = matrix[i][j];
            }
        }
        return new Shape(newMatrix, color);
    }
}

public class TetrisGame extends JPanel {
	private static JFrame frame;
	private static boolean gamePause;

	private Random random = new Random();
    private final int BOARD_WIDTH = 10;
    private final int BOARD_HEIGHT = 20;
    private final int BLOCK_SIZE = 45;
    private final int[][] boardPlayer1 = new int[BOARD_HEIGHT][BOARD_WIDTH];
    private final Color[][] boardColorsPlayer1 = new Color[BOARD_HEIGHT][BOARD_WIDTH];
    private final int[][] boardPlayer2 = new int[BOARD_HEIGHT][BOARD_WIDTH];
    private final Color[][] boardColorsPlayer2 = new Color[BOARD_HEIGHT][BOARD_WIDTH];

    private final Shape[] shapes = new Shape[9];
    private Shape currentShapePlayer1;
    private Shape heldShapePlayer1;
    private Shape currentShapePlayer2;
    private Shape heldShapePlayer2;
	
	private List<Integer> shapesPlayer1;
	private List<Integer> shapesPlayer2;
	private List<Integer> shapesAdjPlayer1;
	private List<Integer> shapesAdjPlayer2;
	private List<Integer> badshapesPlayer1;
	private List<Integer> badshapesPlayer2;
	
	public static int sleepTimePlayer1 = 400;
	public static int sleepTimePlayer2 = 400;
	
	public int whiteTimerPlayer1 = 0;
	public int whiteTimerPlayer2 = 0;
	private static int firstWhitePlayer1 = 0; // 已经经历第一次白色
	private static int firstWhitePlayer2 = 0; // 已经经历第一次白色
	
	private int holdBlockedCounterPlayer1 = 0;
	private int holdBlockedCounterPlayer2 = 0;
	
	public static int skillBlockedTimerPlayer1 = 0;
	public static int skillBlockedTimerPlayer2 = 0;

	private TetrisKeyListener keyListener;
    private BufferedImage textureImage;//
    private BufferedImage redImage;//


    private Color[] shapeColors = {
		new Color(255, 0, 0, 128),     // 红色，透明度为 128
        new Color(255, 128, 0, 128),    // 橙色，透明度为 128
        new Color(255, 255, 0, 128),   // 黄色，透明度为 128
        new Color(0, 255, 0, 128),     // 绿色，透明度为 128
        new Color(0, 255, 255, 128),   // 青色，透明度为 128
        new Color(0, 0, 255, 128),     // 蓝色，透明度为 128
        new Color(255, 0, 255, 128),   // 紫色，透明度为 128
		new Color(128, 128, 128, 128)  // 灰色，透明度为 128
    };

    public TetrisGame() {
		frame = new JFrame("Tetris");
		gamePause = false;
		
        shapes[0] = new Shape(new int[][]{{1, 1, 1, 1}}, shapeColors[0]);
        shapes[1] = new Shape(new int[][]{{1, 1}, {1, 1}}, shapeColors[1]);
        shapes[2] = new Shape(new int[][]{{1, 1, 0}, {0, 1, 1}}, shapeColors[2]);
        shapes[3] = new Shape(new int[][]{{0, 1, 1}, {1, 1, 0}}, shapeColors[3]);
        shapes[4] = new Shape(new int[][]{{0, 1, 0}, {1, 1, 1}}, shapeColors[4]);
        shapes[5] = new Shape(new int[][]{{1, 0, 0}, {1, 1, 1}}, shapeColors[5]);
        shapes[6] = new Shape(new int[][]{{0, 0, 1}, {1, 1, 1}}, shapeColors[6]);
        shapes[7] = new Shape(new int[][]{{0, 1, 1, 0}, {1, 0, 0, 1}/*, {1, 0, 0, 1}, {0, 1, 1, 0}*/}, shapeColors[7]);
		
		shapesPlayer1 = new ArrayList<>(Arrays.asList(0, 1, 2, 3, 4, 5, 6));
		shapesPlayer2 = new ArrayList<>(Arrays.asList(0, 1, 2, 3, 4, 5, 6));
		shapesAdjPlayer1 = new ArrayList<>(Arrays.asList(0, 1, 2, 3, 4, 5, 6));
		shapesAdjPlayer2 = new ArrayList<>(Arrays.asList(0, 1, 2, 3, 4, 5, 6));
		badshapesPlayer1 = new ArrayList<>(Arrays.asList());
		badshapesPlayer2 = new ArrayList<>(Arrays.asList());
		Collections.shuffle(shapesPlayer1);
		Collections.shuffle(shapesPlayer2);
		Collections.shuffle(shapesAdjPlayer1);
		Collections.shuffle(shapesAdjPlayer2);

        currentShapePlayer1 = getRandomShape(shapesPlayer1, shapesAdjPlayer1, badshapesPlayer1);
        currentShapePlayer2 = getRandomShape(shapesPlayer2, shapesAdjPlayer2, badshapesPlayer2);

        setPreferredSize(new Dimension((BOARD_WIDTH + 6) * BLOCK_SIZE * 3, BOARD_HEIGHT * BLOCK_SIZE));
        setBackground(Color.BLACK);
        setFocusable(true);
		
		keyListener = new TetrisKeyListener();
		addKeyListener(keyListener);
    }

    private void placeShapePlayer1() {
        int[][] shapeMatrix = currentShapePlayer1.getMatrix();
        int shapeX = currentShapePlayer1.getX();
        int shapeY = currentShapePlayer1.getY();
        Color shapeColor = currentShapePlayer1.getColor();

        for (int row = 0; row < shapeMatrix.length; row++) {
            for (int col = 0; col < shapeMatrix[row].length; col++) {
                if (shapeMatrix[row][col] != 0) {
                    int boardX = shapeX + col;
                    int boardY = shapeY + row;
					boardPlayer1[boardY][boardX] = shapeMatrix[row][col];
					boardColorsPlayer1[boardY][boardX] = shapeColor;
                }
            }
        }
		
		if (holdBlockedCounterPlayer1 > 0) holdBlockedCounterPlayer1--;
    }

    private void placeShapePlayer2() {
        int[][] shapeMatrix = currentShapePlayer2.getMatrix();
        int shapeX = currentShapePlayer2.getX();
        int shapeY = currentShapePlayer2.getY();
        Color shapeColor = currentShapePlayer2.getColor();

        for (int row = 0; row < shapeMatrix.length; row++) {
            for (int col = 0; col < shapeMatrix[row].length; col++) {
                if (shapeMatrix[row][col] != 0) {
                    int boardX = shapeX + col;
                    int boardY = shapeY + row;
                    boardPlayer2[boardY][boardX] = shapeMatrix[row][col];
                    boardColorsPlayer2[boardY][boardX] = shapeColor;
                }
            }
        }
		
		if (holdBlockedCounterPlayer2 > 0) holdBlockedCounterPlayer2--;
    }

    private void removeFullLinesPlayer1() {
		if (firstWhitePlayer1 == 1 && whiteTimerPlayer1 > 0) return;
		
        int linesRemoved = 0;

        for (int row = BOARD_HEIGHT - 1; row >= 0; row--) {
			boolean lineIsFull = true;
			for (int col = 0; col < BOARD_WIDTH; col++) {
				if (boardPlayer1[row][col] == 0) {
					lineIsFull = false;
					break;
				}
			}
			

			if (lineIsFull) {
				// 增加被刪除的行數
				linesRemoved++;
				
				for (int c = 0; c < BOARD_WIDTH; c++) {
					boardColorsPlayer1[row][c] = Color.WHITE;
				}
				
				repaint();
                revalidate();
			}
		}
		
		if (firstWhitePlayer1 == 1 && whiteTimerPlayer1 == 0)
		{
			removeAllFullLinesPlayer1();
			firstWhitePlayer1 = 0;
		}		
		else if (linesRemoved > 0 && whiteTimerPlayer1 == 0)
		{
			firstWhitePlayer1 = 1;
			whiteTimerPlayer1 = 1;
		}
    }
	
	
	private void removeAllFullLinesPlayer1() {
		int linesRemoved = 0;

		for (int row = BOARD_HEIGHT - 1; row >= 0; row--) {
			boolean lineIsFull = true;
			for (int col = 0; col < BOARD_WIDTH; col++) {
				if (boardPlayer1[row][col] == 0) {
					lineIsFull = false;
					break;
				}
			}

			if (lineIsFull) {
				// 增加被刪除的行數
				linesRemoved++;

				// 更新被刪除行以上的方塊狀態
				for (int r = row; r > 0; r--) {
					for (int c = 0; c < BOARD_WIDTH; c++) {
						boardPlayer1[r][c] = boardPlayer1[r - 1][c];
						boardColorsPlayer1[r][c] = boardColorsPlayer1[r - 1][c];
					}
				}
				
				// 清空最頂行的方塊
				for (int c = 0; c < BOARD_WIDTH; c++) {
					boardPlayer1[0][c] = 0;
					boardColorsPlayer1[0][c] = Color.BLACK;
				}

				// 檢查下一行
				row++;
			}
		}
		
		switch (linesRemoved) {
			case 1:
				if (skillBlockedTimerPlayer1 == 0)
					skill1("player1");
				break;
			case 2:
				if (skillBlockedTimerPlayer1 == 0)
					skill2("player1");
				break;
			case 3:
				if (skillBlockedTimerPlayer1 == 0)
					skill3("player1");
				break;
			case 4:
				skill4("player1");
				break;
		}
		
		boolean boardEmpty = true;
		for (int row = BOARD_HEIGHT - 1; row >= 0; row--) {
			for (int col = 0; col < BOARD_WIDTH; col++)
				if (boardPlayer1[row][col] == 1) {
					boardEmpty = false;
					break;
				}
			if (boardEmpty == false)
				break;
		}
		
		if (boardEmpty)
			skillBoardEmpty("player1");
    }

    private void removeFullLinesPlayer2() {
        if (firstWhitePlayer2 == 1 && whiteTimerPlayer2 > 0) return;
		
        int linesRemoved = 0;

        for (int row = BOARD_HEIGHT - 1; row >= 0; row--) {
			boolean lineIsFull = true;
			for (int col = 0; col < BOARD_WIDTH; col++) {
				if (boardPlayer2[row][col] == 0) {
					lineIsFull = false;
					break;
				}
			}
			

			if (lineIsFull) {
				// 增加被刪除的行數
				linesRemoved++;
				
				for (int c = 0; c < BOARD_WIDTH; c++) {
					boardColorsPlayer2[row][c] = Color.WHITE;
				}
				
				repaint();
                revalidate();
			}
		}
		
		if (firstWhitePlayer2 == 1 && whiteTimerPlayer2 == 0)
		{
			removeAllFullLinesPlayer2();
			firstWhitePlayer2 = 0;
		}		
		else if (linesRemoved > 0 && whiteTimerPlayer2 == 0)
		{
			firstWhitePlayer2 = 1;
			whiteTimerPlayer2 = 1;
		}
    }
	
	private void removeAllFullLinesPlayer2() {
		int linesRemoved = 0;

		for (int row = BOARD_HEIGHT - 1; row >= 0; row--) {
			boolean lineIsFull = true;
			for (int col = 0; col < BOARD_WIDTH; col++) {
				if (boardPlayer2[row][col] == 0) {
					lineIsFull = false;
					break;
				}
			}

			if (lineIsFull) {
				// 增加被刪除的行數
				linesRemoved++;

				// 更新被刪除行以上的方塊狀態
				for (int r = row; r > 0; r--) {
					for (int c = 0; c < BOARD_WIDTH; c++) {
						boardPlayer2[r][c] = boardPlayer2[r - 1][c];
						boardColorsPlayer2[r][c] = boardColorsPlayer2[r - 1][c];
					}
				}
				
				// 清空最頂行的方塊
				for (int c = 0; c < BOARD_WIDTH; c++) {
					boardPlayer2[0][c] = 0;
					boardColorsPlayer2[0][c] = Color.BLACK;
				}

				// 檢查下一行
				row++;
			}
		}
				
		switch (linesRemoved) {
			case 1:
				if (skillBlockedTimerPlayer2 == 0)
					skill1("player2");
				break;
			case 2:
				if (skillBlockedTimerPlayer2 == 0)
					skill2("player2");
				break;
			case 3:
				if (skillBlockedTimerPlayer2 == 0)
					skill3("player2");
				break;
			case 4:
				skill4("player2");
				break;
		}
		
		boolean boardEmpty = true;
		for (int row = BOARD_HEIGHT - 1; row >= 0; row--) {
			for (int col = 0; col < BOARD_WIDTH; col++)
				if (boardPlayer2[row][col] == 1) {
					boardEmpty = false;
					break;
				}
			if (boardEmpty == false)
				break;
		}
		
		if (boardEmpty)
			skillBoardEmpty("player2");
    }
	
	// drop speed
	public void skill1(String player){
		if(player == "player1")
		{
			if (sleepTimePlayer1 < 275) sleepTimePlayer1 += 5;
			else sleepTimePlayer2 -= 5;
		}
		else if(player == "player2")
		{
			if (sleepTimePlayer2 < 275) sleepTimePlayer2 += 5;
			else sleepTimePlayer1 -= 5;
		}
	}
	
	// bad shape
	public void skill3(String player){
		if(player == "player1")
		{
			// skill3
			boolean gray = false;
			boolean fillGray = false;
			for (int r = 0; r < BOARD_HEIGHT; r++) {
				for (int c = 0; c < BOARD_WIDTH; c++) {
					if (boardColorsPlayer1[r][c] == shapeColors[7])
						gray = true;
				}
				if (gray == true)
					break;
			}	
			
			if(gray)
			{
				for (int r = 0; r < BOARD_HEIGHT; r++)
				{
					for (int c = 0; c < BOARD_WIDTH; c++)
					{
						if (boardColorsPlayer1[r][c] == shapeColors[7])
						{
							if (r - 1 >= 0 && r - 1 < BOARD_HEIGHT && c - 1 >= 0 && c - 1 < BOARD_WIDTH)
								if (boardColorsPlayer1[r - 1][c - 1] == shapeColors[7])
								{
									if (boardPlayer1[r - 1][c] == 0) fillGray = true;
									boardPlayer1[r - 1][c] = 1;
									boardColorsPlayer1[r - 1][c] = shapeColors[7];
									
									if (boardPlayer1[r][c - 1] == 0) fillGray = true;
									boardPlayer1[r][c - 1] = 1;
									boardColorsPlayer1[r][c - 1] = shapeColors[7];
								}
								
							if (r - 1 >= 0 && r - 1 < BOARD_HEIGHT && c + 1 >= 0 && c + 1 < BOARD_WIDTH)
								if (boardColorsPlayer1[r - 1][c + 1] == shapeColors[7])
								{
									if (boardPlayer1[r - 1][c] == 0) fillGray = true;
									boardPlayer1[r - 1][c] = 1;
									boardColorsPlayer1[r - 1][c] = shapeColors[7];
									
									if (boardPlayer1[r][c + 1] == 0) fillGray = true;
									boardPlayer1[r][c + 1] = 1;
									boardColorsPlayer1[r][c + 1] = shapeColors[7];
								}
								
							if (r + 1 >= 0 && r + 1 < BOARD_HEIGHT && c - 1 >= 0 && c - 1 < BOARD_WIDTH)
								if (boardColorsPlayer1[r + 1][c - 1] == shapeColors[7])
								{
									if (boardPlayer1[r + 1][c] == 0) fillGray = true;
									boardPlayer1[r + 1][c] = 1;
									boardColorsPlayer1[r + 1][c] = shapeColors[7];
									
									if (boardPlayer1[r][c - 1] == 0) fillGray = true;
									boardPlayer1[r][c - 1] = 1;
									boardColorsPlayer1[r][c - 1] = shapeColors[7];
								}
								
							if (r + 1 >= 0 && r + 1 < BOARD_HEIGHT && c + 1 >= 0 && c + 1 < BOARD_WIDTH)
								if (boardColorsPlayer1[r + 1][c + 1] == shapeColors[7])
								{
									if (boardPlayer1[r + 1][c] == 0) fillGray = true;
									boardPlayer1[r + 1][c] = 1;
									boardColorsPlayer1[r + 1][c] = shapeColors[7];
									
									if (boardPlayer1[r][c + 1] == 0) fillGray = true;
									boardPlayer1[r][c + 1] = 1;
									boardColorsPlayer1[r][c + 1] = shapeColors[7];
								}
						}
					}
				}
			}
			if (!gray || !fillGray)
				badshapesPlayer2.addAll(Arrays.asList(7, 7));
		}
		else if(player == "player2")
		{
			// skill3
			boolean gray = false;
			boolean fillGray = false;
			for (int r = 0; r < BOARD_HEIGHT; r++) {
				for (int c = 0; c < BOARD_WIDTH; c++) {
					if (boardColorsPlayer2[r][c] == shapeColors[7])
						gray = true;
				}
				if (gray == true)
					break;
			}	
			
			if(gray)
			{
				for (int r = 0; r < BOARD_HEIGHT; r++)
				{
					for (int c = 0; c < BOARD_WIDTH; c++)
					{
						if (boardColorsPlayer2[r][c] == shapeColors[7])
						{
							if (r - 1 >= 0 && r - 1 < BOARD_HEIGHT && c - 1 >= 0 && c - 1 < BOARD_WIDTH)
								if (boardColorsPlayer2[r - 1][c - 1] == shapeColors[7])
								{
									if (boardPlayer2[r - 1][c] == 0) fillGray = true;
									boardPlayer2[r - 1][c] = 1;
									boardColorsPlayer2[r - 1][c] = shapeColors[7];
									
									if (boardPlayer2[r][c - 1] == 0) fillGray = true;
									boardPlayer2[r][c - 1] = 1;
									boardColorsPlayer2[r][c - 1] = shapeColors[7];
								}
								
							if (r - 1 >= 0 && r - 1 < BOARD_HEIGHT && c + 1 >= 0 && c + 1 < BOARD_WIDTH)
								if (boardColorsPlayer2[r - 1][c + 1] == shapeColors[7])
								{
									if (boardPlayer2[r - 1][c] == 0) fillGray = true;
									boardPlayer2[r - 1][c] = 1;
									boardColorsPlayer2[r - 1][c] = shapeColors[7];
									
									if (boardPlayer2[r][c + 1] == 0) fillGray = true;
									boardPlayer2[r][c + 1] = 1;
									boardColorsPlayer2[r][c + 1] = shapeColors[7];
								}
								
							if (r + 1 >= 0 && r + 1 < BOARD_HEIGHT && c - 1 >= 0 && c - 1 < BOARD_WIDTH)
								if (boardColorsPlayer2[r + 1][c - 1] == shapeColors[7])
								{
									if (boardPlayer2[r + 1][c] == 0) fillGray = true;
									boardPlayer2[r + 1][c] = 1;
									boardColorsPlayer2[r + 1][c] = shapeColors[7];
									
									if (boardPlayer2[r][c - 1] == 0) fillGray = true;
									boardPlayer2[r][c - 1] = 1;
									boardColorsPlayer2[r][c - 1] = shapeColors[7];
								}
								
							if (r + 1 >= 0 && r + 1 < BOARD_HEIGHT && c + 1 >= 0 && c + 1 < BOARD_WIDTH)
								if (boardColorsPlayer2[r + 1][c + 1] == shapeColors[7])
								{
									if (boardPlayer2[r + 1][c] == 0) fillGray = true;
									boardPlayer2[r + 1][c] = 1;
									boardColorsPlayer2[r + 1][c] = shapeColors[7];
									
									if (boardPlayer2[r][c + 1] == 0) fillGray = true;
									boardPlayer2[r][c + 1] = 1;
									boardColorsPlayer2[r][c + 1] = shapeColors[7];
								}
						}
					}
				}
			}
			if (!gray || !fillGray)
				badshapesPlayer1.addAll(Arrays.asList(7, 7));
		}
	}
	
	// hold block
	public void skill2(String player){
		if(player == "player1")
		{
			for(int i = 0; i < 5; i++)
			{
				if (holdBlockedCounterPlayer1 > 0)
					holdBlockedCounterPlayer1--;
				else
					holdBlockedCounterPlayer2++;
			}
		}
		else if(player == "player2")
		{
			for(int i = 0; i < 5; i++)
			{
				if (holdBlockedCounterPlayer2 > 0)
					holdBlockedCounterPlayer2--;
				else
					holdBlockedCounterPlayer1++;
			}
		}
	}
	
	// (skill 1~3 ) : remove all debuff or exert debuff ome time
	// Increases the opponent's disable effect for 15 seconds
	public void skill4(String player){
		if(player == "player1")
		{
			if (sleepTimePlayer1 < 275) sleepTimePlayer1 = 275; // skill1
			else sleepTimePlayer2 -= 5;
			
			// skill3
			boolean gray = false;
			boolean fillGray = false;
			for (int r = 0; r < BOARD_HEIGHT; r++) {
				for (int c = 0; c < BOARD_WIDTH; c++) {
					if (boardColorsPlayer1[r][c] == shapeColors[7])
						gray = true;
				}
				if (gray == true)
					break;
			}	
			
			if(gray)
			{
				for (int r = 0; r < BOARD_HEIGHT; r++)
				{
					for (int c = 0; c < BOARD_WIDTH; c++)
					{
						if (boardColorsPlayer1[r][c] == shapeColors[7])
						{
							if (r - 1 >= 0 && r - 1 < BOARD_HEIGHT && c - 1 >= 0 && c - 1 < BOARD_WIDTH)
								if (boardColorsPlayer1[r - 1][c - 1] == shapeColors[7])
								{
									if (boardPlayer1[r - 1][c] == 0) fillGray = true;
									boardPlayer1[r - 1][c] = 1;
									boardColorsPlayer1[r - 1][c] = shapeColors[7];
									
									if (boardPlayer1[r][c - 1] == 0) fillGray = true;
									boardPlayer1[r][c - 1] = 1;
									boardColorsPlayer1[r][c - 1] = shapeColors[7];
								}
								
							if (r - 1 >= 0 && r - 1 < BOARD_HEIGHT && c + 1 >= 0 && c + 1 < BOARD_WIDTH)
								if (boardColorsPlayer1[r - 1][c + 1] == shapeColors[7])
								{
									if (boardPlayer1[r - 1][c] == 0) fillGray = true;
									boardPlayer1[r - 1][c] = 1;
									boardColorsPlayer1[r - 1][c] = shapeColors[7];
									
									if (boardPlayer1[r][c + 1] == 0) fillGray = true;
									boardPlayer1[r][c + 1] = 1;
									boardColorsPlayer1[r][c + 1] = shapeColors[7];
								}
								
							if (r + 1 >= 0 && r + 1 < BOARD_HEIGHT && c - 1 >= 0 && c - 1 < BOARD_WIDTH)
								if (boardColorsPlayer1[r + 1][c - 1] == shapeColors[7])
								{
									if (boardPlayer1[r + 1][c] == 0) fillGray = true;
									boardPlayer1[r + 1][c] = 1;
									boardColorsPlayer1[r + 1][c] = shapeColors[7];
									
									if (boardPlayer1[r][c - 1] == 0) fillGray = true;
									boardPlayer1[r][c - 1] = 1;
									boardColorsPlayer1[r][c - 1] = shapeColors[7];
								}
								
							if (r + 1 >= 0 && r + 1 < BOARD_HEIGHT && c + 1 >= 0 && c + 1 < BOARD_WIDTH)
								if (boardColorsPlayer1[r + 1][c + 1] == shapeColors[7])
								{
									if (boardPlayer1[r + 1][c] == 0) fillGray = true;
									boardPlayer1[r + 1][c] = 1;
									boardColorsPlayer1[r + 1][c] = shapeColors[7];
									
									if (boardPlayer1[r][c + 1] == 0) fillGray = true;
									boardPlayer1[r][c + 1] = 1;
									boardColorsPlayer1[r][c + 1] = shapeColors[7];
								}
						}
					}
				}
			}
			if (!gray || !fillGray)
				badshapesPlayer2.addAll(Arrays.asList(7, 7));
			
			if(holdBlockedCounterPlayer1 > 0) // skill2
				holdBlockedCounterPlayer1 = 0;
			else
				holdBlockedCounterPlayer2 += 5;

			skillBlockedTimerPlayer2 += 15000; // muteki
		}
		else if(player == "player2")
		{
			if (sleepTimePlayer2 < 275) sleepTimePlayer2 = 275; // skill1
			else sleepTimePlayer1 -= 5;
			
			// skill3
			boolean gray = false;
			boolean fillGray = false;
			for (int r = 0; r < BOARD_HEIGHT; r++) {
				for (int c = 0; c < BOARD_WIDTH; c++) {
					if (boardColorsPlayer2[r][c] == shapeColors[7])
						gray = true;
				}
				if (gray == true)
					break;
			}	
			
			if(gray)
			{
				for (int r = 0; r < BOARD_HEIGHT; r++)
				{
					for (int c = 0; c < BOARD_WIDTH; c++)
					{
						if (boardColorsPlayer2[r][c] == shapeColors[7])
						{
							if (r - 1 >= 0 && r - 1 < BOARD_HEIGHT && c - 1 >= 0 && c - 1 < BOARD_WIDTH)
								if (boardColorsPlayer2[r - 1][c - 1] == shapeColors[7])
								{
									if (boardPlayer2[r - 1][c] == 0) fillGray = true;
									boardPlayer2[r - 1][c] = 1;
									boardColorsPlayer2[r - 1][c] = shapeColors[7];
									
									if (boardPlayer2[r][c - 1] == 0) fillGray = true;
									boardPlayer2[r][c - 1] = 1;
									boardColorsPlayer2[r][c - 1] = shapeColors[7];
								}
								
							if (r - 1 >= 0 && r - 1 < BOARD_HEIGHT && c + 1 >= 0 && c + 1 < BOARD_WIDTH)
								if (boardColorsPlayer2[r - 1][c + 1] == shapeColors[7])
								{
									if (boardPlayer2[r - 1][c] == 0) fillGray = true;
									boardPlayer2[r - 1][c] = 1;
									boardColorsPlayer2[r - 1][c] = shapeColors[7];
									
									if (boardPlayer2[r][c + 1] == 0) fillGray = true;
									boardPlayer2[r][c + 1] = 1;
									boardColorsPlayer2[r][c + 1] = shapeColors[7];
								}
								
							if (r + 1 >= 0 && r + 1 < BOARD_HEIGHT && c - 1 >= 0 && c - 1 < BOARD_WIDTH)
								if (boardColorsPlayer2[r + 1][c - 1] == shapeColors[7])
								{
									if (boardPlayer2[r + 1][c] == 0) fillGray = true;
									boardPlayer2[r + 1][c] = 1;
									boardColorsPlayer2[r + 1][c] = shapeColors[7];
									
									if (boardPlayer2[r][c - 1] == 0) fillGray = true;
									boardPlayer2[r][c - 1] = 1;
									boardColorsPlayer2[r][c - 1] = shapeColors[7];
								}
								
							if (r + 1 >= 0 && r + 1 < BOARD_HEIGHT && c + 1 >= 0 && c + 1 < BOARD_WIDTH)
								if (boardColorsPlayer2[r + 1][c + 1] == shapeColors[7])
								{
									if (boardPlayer2[r + 1][c] == 0) fillGray = true;
									boardPlayer2[r + 1][c] = 1;
									boardColorsPlayer2[r + 1][c] = shapeColors[7];
									
									if (boardPlayer2[r][c + 1] == 0) fillGray = true;
									boardPlayer2[r][c + 1] = 1;
									boardColorsPlayer2[r][c + 1] = shapeColors[7];
								}
						}
					}
				}
			}
			if (!gray || !fillGray)
				badshapesPlayer1.addAll(Arrays.asList(7, 7));
			
			if(holdBlockedCounterPlayer2 > 0) // skill2
				holdBlockedCounterPlayer2 = 0;
			else
				holdBlockedCounterPlayer1 += 5;

			skillBlockedTimerPlayer1 += 15000; // muteki
		}
	}
	
	public void skillBoardEmpty(String player){
		if(player == "player1")
		{			
			boolean rivalLose = false;
			
			for (int r = 0; r < 4; r++) {
				for (int col = 0; col < BOARD_WIDTH; col++) {
					if (boardPlayer2[r][col] == 1) {
						rivalLose = true;
						break;
					}
				}
			}
					
			for (int r = 0; r < BOARD_HEIGHT - 4; r++) {
				for (int c = 0; c < BOARD_WIDTH; c++) {
					boardPlayer2[r][c] = boardPlayer2[r + 4][c];
					boardColorsPlayer2[r][c] = boardColorsPlayer2[r + 4][c];
				}
			}	

			for (int c = 0; c < BOARD_WIDTH; c++)
			{
				if (c % 2 == 0)
				{
					boardPlayer2[BOARD_HEIGHT - 4][c] = 1;
					boardColorsPlayer2[BOARD_HEIGHT - 4][c] = Color.WHITE;
					boardPlayer2[BOARD_HEIGHT - 3][c] = 0;
					boardColorsPlayer2[BOARD_HEIGHT - 3][c] = Color.BLACK;
					boardPlayer2[BOARD_HEIGHT - 2][c] = 1;
					boardColorsPlayer2[BOARD_HEIGHT - 2][c] = Color.WHITE;
					boardPlayer2[BOARD_HEIGHT - 1][c] = 0;
					boardColorsPlayer2[BOARD_HEIGHT - 1][c] = Color.BLACK;
				}
				else
				{
					boardPlayer2[BOARD_HEIGHT - 4][c] = 0;
					boardColorsPlayer2[BOARD_HEIGHT - 4][c] = Color.BLACK;
					boardPlayer2[BOARD_HEIGHT - 3][c] = 1;
					boardColorsPlayer2[BOARD_HEIGHT - 3][c] = Color.WHITE;
					boardPlayer2[BOARD_HEIGHT - 2][c] = 0;
					boardColorsPlayer2[BOARD_HEIGHT - 2][c] = Color.BLACK;
					boardPlayer2[BOARD_HEIGHT - 1][c] = 1;
					boardColorsPlayer2[BOARD_HEIGHT - 1][c] = Color.WHITE;
				}
			}			

			repaint();
			revalidate();
			
			if (rivalLose) {
				resetGamePlayer2();
			}
		}
		else if(player == "player2")
		{
			boolean rivalLose = false;
			for (int r = 0; r < 4; r++) {
				for (int col = 0; col < BOARD_WIDTH; col++) {
					if (boardPlayer1[r][col] == 1) {
						rivalLose = true;
						break;
					}
				}
			}
					
			for (int r = 0; r < BOARD_HEIGHT - 4; r++) {
				for (int c = 0; c < BOARD_WIDTH; c++) {
					boardPlayer1[r][c] = boardPlayer1[r + 4][c];
					boardColorsPlayer1[r][c] = boardColorsPlayer1[r + 4][c];
				}
			}	

			for (int c = 0; c < BOARD_WIDTH; c++)
			{
				if (c % 2 == 0)
				{
					boardPlayer1[BOARD_HEIGHT - 4][c] = 1;
					boardColorsPlayer1[BOARD_HEIGHT - 4][c] = Color.WHITE;
					boardPlayer1[BOARD_HEIGHT - 3][c] = 0;
					boardColorsPlayer1[BOARD_HEIGHT - 3][c] = Color.BLACK;
					boardPlayer1[BOARD_HEIGHT - 2][c] = 1;
					boardColorsPlayer1[BOARD_HEIGHT - 2][c] = Color.WHITE;
					boardPlayer1[BOARD_HEIGHT - 1][c] = 0;
					boardColorsPlayer1[BOARD_HEIGHT - 1][c] = Color.BLACK;
				}
				else
				{
					boardPlayer1[BOARD_HEIGHT - 4][c] = 0;
					boardColorsPlayer1[BOARD_HEIGHT - 4][c] = Color.BLACK;
					boardPlayer1[BOARD_HEIGHT - 3][c] = 1;
					boardColorsPlayer1[BOARD_HEIGHT - 3][c] = Color.WHITE;
					boardPlayer1[BOARD_HEIGHT - 2][c] = 0;
					boardColorsPlayer1[BOARD_HEIGHT - 2][c] = Color.BLACK;
					boardPlayer1[BOARD_HEIGHT - 1][c] = 1;
					boardColorsPlayer1[BOARD_HEIGHT - 1][c] = Color.WHITE;
				}
			}			

			repaint();
			revalidate();
			
			if (rivalLose) {
				resetGamePlayer1();
			}
		}
	}


    private boolean canMoveLeftPlayer1() {
        int[][] shapeMatrix = currentShapePlayer1.getMatrix();
        int shapeX = currentShapePlayer1.getX();
        int shapeY = currentShapePlayer1.getY();

        for (int row = 0; row < shapeMatrix.length; row++) {
            for (int col = 0; col < shapeMatrix[row].length; col++) {
                if (shapeMatrix[row][col] != 0) {
                    int boardX = shapeX + col - 1;
                    int boardY = shapeY + row;
                    if (boardX < 0 || boardY < 0 || boardY >= BOARD_HEIGHT || (boardX >= 0 && boardPlayer1[boardY][boardX] != 0)) {
                        return false;
                    }
                }
            }
        }
        return true;
    }

    private boolean canMoveLeftPlayer2() {
        int[][] shapeMatrix = currentShapePlayer2.getMatrix();
        int shapeX = currentShapePlayer2.getX();
        int shapeY = currentShapePlayer2.getY();

        for (int row = 0; row < shapeMatrix.length; row++) {
            for (int col = 0; col < shapeMatrix[row].length; col++) {
                if (shapeMatrix[row][col] != 0) {
                    int boardX = shapeX + col - 1;
                    int boardY = shapeY + row;
                    if (boardX < 0 || boardY < 0 || boardY >= BOARD_HEIGHT || (boardX >= 0 && boardPlayer2[boardY][boardX] != 0)) {
                        return false;
                    }
                }
            }
        }
        return true;
    }

    private boolean canMoveRightPlayer1() {
        int[][] shapeMatrix = currentShapePlayer1.getMatrix();
        int shapeX = currentShapePlayer1.getX();
        int shapeY = currentShapePlayer1.getY();

        for (int row = 0; row < shapeMatrix.length; row++) {
            for (int col = 0; col < shapeMatrix[row].length; col++) {
                if (shapeMatrix[row][col] != 0) {
                    int boardX = shapeX + col + 1;
                    int boardY = shapeY + row;
                    if (boardX >= BOARD_WIDTH || boardY < 0 || boardY >= BOARD_HEIGHT || (boardX < BOARD_WIDTH && boardPlayer1[boardY][boardX] != 0)) {
                        return false;
                    }
                }
            }
        }
        return true;
    }

    private boolean canMoveRightPlayer2() {
        int[][] shapeMatrix = currentShapePlayer2.getMatrix();
        int shapeX = currentShapePlayer2.getX();
        int shapeY = currentShapePlayer2.getY();

        for (int row = 0; row < shapeMatrix.length; row++) {
            for (int col = 0; col < shapeMatrix[row].length; col++) {
                if (shapeMatrix[row][col] != 0) {
                    int boardX = shapeX + col + 1;
                    int boardY = shapeY + row;
                    if (boardX >= BOARD_WIDTH || boardY < 0 || boardY >= BOARD_HEIGHT || (boardX < BOARD_WIDTH && boardPlayer2[boardY][boardX] != 0)) {
                        return false;
                    }
                }
            }
        }
        return true;
    }

    private boolean canMoveDownPlayer1() {
        int[][] shapeMatrix = currentShapePlayer1.getMatrix();
        int shapeX = currentShapePlayer1.getX();
        int shapeY = currentShapePlayer1.getY();

        for (int row = 0; row < shapeMatrix.length; row++) {
            for (int col = 0; col < shapeMatrix[row].length; col++) {
                if (shapeMatrix[row][col] != 0) {
                    int boardX = shapeX + col;
                    int boardY = shapeY + row + 1;
                    if (boardY >= BOARD_HEIGHT || (boardY < BOARD_HEIGHT && boardPlayer1[boardY][boardX] != 0)) {
                        return false;
                    }
                }
            }
        }
        return true;
    }

    private boolean canMoveDownPlayer2() {
        int[][] shapeMatrix = currentShapePlayer2.getMatrix();
        int shapeX = currentShapePlayer2.getX();
        int shapeY = currentShapePlayer2.getY();

        for (int row = 0; row < shapeMatrix.length; row++) {
            for (int col = 0; col < shapeMatrix[row].length; col++) {
                if (shapeMatrix[row][col] != 0) {
                    int boardX = shapeX + col;
                    int boardY = shapeY + row + 1;
                    if (boardY >= BOARD_HEIGHT || (boardY < BOARD_HEIGHT && boardPlayer2[boardY][boardX] != 0)) {
                        return false;
                    }
                }
            }
        }
        return true;
    }

    private void rotateShapePlayer1() {
        Shape rotatedShape = currentShapePlayer1.rotate();
        int rotatedX = currentShapePlayer1.getX();
        int rotatedY = currentShapePlayer1.getY();

        if (rotatedX < 0) {
            rotatedX = 0;
        } else if (rotatedX + rotatedShape.getMatrix()[0].length > BOARD_WIDTH) {
            rotatedX = BOARD_WIDTH - rotatedShape.getMatrix()[0].length;
        }

        if (rotatedY + rotatedShape.getMatrix().length > BOARD_HEIGHT) {
            rotatedY = BOARD_HEIGHT - rotatedShape.getMatrix().length;
        }

        rotatedShape.setX(rotatedX);
        rotatedShape.setY(rotatedY);

        if (isValidPositionPlayer1(rotatedShape)) {
            currentShapePlayer1 = rotatedShape;
        }
    }

    private void rotateShapePlayer2() {
        Shape rotatedShape = currentShapePlayer2.rotate();
        int rotatedX = currentShapePlayer2.getX();
        int rotatedY = currentShapePlayer2.getY();

        if (rotatedX < 0) {
            rotatedX = 0;
        } else if (rotatedX + rotatedShape.getMatrix()[0].length > BOARD_WIDTH) {
            rotatedX = BOARD_WIDTH - rotatedShape.getMatrix()[0].length;
        }

        if (rotatedY + rotatedShape.getMatrix().length > BOARD_HEIGHT) {
            rotatedY = BOARD_HEIGHT - rotatedShape.getMatrix().length;
        }

        rotatedShape.setX(rotatedX);
        rotatedShape.setY(rotatedY);

        if (isValidPositionPlayer2(rotatedShape)) {
            currentShapePlayer2 = rotatedShape;
        }
    }

    private boolean isValidPositionPlayer1(Shape shape) {
        int[][] shapeMatrix = shape.getMatrix();
        int shapeX = shape.getX();
        int shapeY = shape.getY();

        for (int row = 0; row < shapeMatrix.length; row++) {
            for (int col = 0; col < shapeMatrix[row].length; col++) {
                if (shapeMatrix[row][col] != 0) {
                    int boardX = shapeX + col;
                    int boardY = shapeY + row;
                    if (boardX < 0 || boardX >= BOARD_WIDTH || boardY >= BOARD_HEIGHT || boardPlayer1[boardY][boardX] != 0) {
                        return false;
                    }
                }
            }
        }
        return true;
    }

    private boolean isValidPositionPlayer2(Shape shape) {
        int[][] shapeMatrix = shape.getMatrix();
        int shapeX = shape.getX();
        int shapeY = shape.getY();

        for (int row = 0; row < shapeMatrix.length; row++) {
            for (int col = 0; col < shapeMatrix[row].length; col++) {
                if (shapeMatrix[row][col] != 0) {
                    int boardX = shapeX + col;
                    int boardY = shapeY + row;
                    if (boardX < 0 || boardX >= BOARD_WIDTH || boardY >= BOARD_HEIGHT || boardPlayer2[boardY][boardX] != 0) {
                        return false;
                    }
                }
            }
        }
        return true;
    }

    private Shape getRandomShape(List<Integer> shapesX, List<Integer> shapesAdj, List<Integer> badshapes) {
		if (shapesAdj.isEmpty()) {
            shapesAdj.addAll(Arrays.asList(0, 1, 2, 3, 4, 5, 6));
			Collections.shuffle(shapesAdj);
		}
		
		int index;
		
		if (badshapes.isEmpty()) {
			index = (int)shapesX.remove(0);
			
			shapesX.add(shapesAdj.get(0)); // 將 List2 的第一個元素插入 List1 的最後
			shapesAdj.remove(0); // 移除 List2 的第一個元素
		}
		else {
			index = (int)badshapes.remove(0);
		}

        return new Shape(shapes[index].getMatrix(), shapes[index].getColor());
    }

    private void drawGuideLinePlayer1(Graphics g) {
        int[][] shapeMatrix = currentShapePlayer1.getMatrix();
        int shapeX = currentShapePlayer1.getX();
        int shapeY = currentShapePlayer1.getY();

        int guideY = shapeY;
        while (canMoveDownPlayer1()) {
            guideY++;
            currentShapePlayer1.moveDown();
        }

        currentShapePlayer1.setY(shapeY);

        for (int row = 0; row < shapeMatrix.length; row++) {
            for (int col = 0; col < shapeMatrix[row].length; col++) {
                if (shapeMatrix[row][col] != 0) {
                    int x = (shapeX + col) * BLOCK_SIZE;
                    int y = (guideY + row) * BLOCK_SIZE;
                    Color color = currentShapePlayer1.getColor();
                    g.setColor(new Color(color.getRed(), color.getGreen(), color.getBlue(), 100));
                    g.fillRect(x+200, y, BLOCK_SIZE, BLOCK_SIZE);
                }
            }
        }
    }

    private void drawGuideLinePlayer2(Graphics g) {
        int[][] shapeMatrix = currentShapePlayer2.getMatrix();
        int shapeX = currentShapePlayer2.getX();
        int shapeY = currentShapePlayer2.getY();

        int guideY = shapeY;
        while (canMoveDownPlayer2()) {
            guideY++;
            currentShapePlayer2.moveDown();
        }

        currentShapePlayer2.setY(shapeY);

        for (int row = 0; row < shapeMatrix.length; row++) {
            for (int col = 0; col < shapeMatrix[row].length; col++) {
                if (shapeMatrix[row][col] != 0) {
                    int x = (shapeX + col + BOARD_WIDTH + 4) * BLOCK_SIZE;
                    int y = (guideY + row) * BLOCK_SIZE;
                    Color color = currentShapePlayer2.getColor();
                    g.setColor(new Color(color.getRed(), color.getGreen(), color.getBlue(), 100));
                    g.fillRect(x+420, y, BLOCK_SIZE, BLOCK_SIZE);
                }
            }
        }
    }

    @Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g);
		Graphics2D g2d = (Graphics2D) g;

        try {
            // 加载纹理图片
            textureImage = ImageIO.read(getClass().getResource("texture.png"));
        } catch (Exception e) {
            e.printStackTrace();
        }

        try {
            // 加载纹理图片
            redImage = ImageIO.read(getClass().getResource("red.png"));
        } catch (Exception e) {
            e.printStackTrace();
        }

        int blockOffset = BLOCK_SIZE + 2;

        // 蝏�摰嗡����
        g2d.setColor(Color.GRAY);
        for (int row = 0; row < BOARD_HEIGHT; row++) {
            for (int col = 0; col < BOARD_WIDTH; col++) {
                int x = col * BLOCK_SIZE;
                int y = row * BLOCK_SIZE;
                g2d.drawRect(x+200, y, BLOCK_SIZE, BLOCK_SIZE);
            }
        }

		//if (!gamePause)
			for (int row = 0; row < BOARD_HEIGHT; row++) {
				for (int col = 0; col < BOARD_WIDTH; col++) {
					int x = col * BLOCK_SIZE;
					int y = row * BLOCK_SIZE;
					int value = boardPlayer1[row][col];

					if (value != 0) {
						Color color = boardColorsPlayer1[row][col];
						Color endColor = Color.WHITE;
						g2d.setColor(color);
						
						// 设置绘制的渐变颜色
						GradientPaint gradientPaint = new GradientPaint(x+200, y, color, x +200+ BLOCK_SIZE, y + BLOCK_SIZE, endColor);
						g2d.setPaint(gradientPaint);
						// 绘制纹理图片
						g2d.drawImage(textureImage, x+200, y, x+200 + BLOCK_SIZE, y + BLOCK_SIZE, 0, 0, textureImage.getWidth(), textureImage.getHeight(), null);

						// 填充方块
						g2d.fillRect(x+200, y, BLOCK_SIZE, BLOCK_SIZE);
						g2d.setColor(Color.BLACK);
						g2d.drawRect(x+200, y, BLOCK_SIZE, BLOCK_SIZE);
					}
				}
			}

        int[][] shapeMatrixPlayer1 = currentShapePlayer1.getMatrix();
        int shapeXPlayer1 = currentShapePlayer1.getX();
        int shapeYPlayer1 = currentShapePlayer1.getY();

        for (int row = 0; row < shapeMatrixPlayer1.length; row++) {
            for (int col = 0; col < shapeMatrixPlayer1[row].length; col++) {
                if (shapeMatrixPlayer1[row][col] != 0) {
                    int x = (shapeXPlayer1 + col) * BLOCK_SIZE;
                    int y = (shapeYPlayer1 + row) * BLOCK_SIZE;
                    Color color = currentShapePlayer1.getColor();
					Color endColor = Color.WHITE;
                    g2d.setColor(color);
					
					GradientPaint gradientPaint = new GradientPaint(x+200, y, color, x+200+BLOCK_SIZE, y + BLOCK_SIZE, endColor);
					g2d.setPaint(gradientPaint);
					// 绘制纹理图片
                    g2d.drawImage(textureImage, x+200, y, x+200 + BLOCK_SIZE, y + BLOCK_SIZE, 0, 0, textureImage.getWidth(), textureImage.getHeight(), null);
					
                    g2d.fillRect(x+200, y, BLOCK_SIZE, BLOCK_SIZE);
                    g2d.setColor(Color.BLACK);
                    g2d.drawRect(x+200, y, BLOCK_SIZE, BLOCK_SIZE);
                }
            }
        }

        // 蝏�摰嗡���� hold ����
        int holdXPlayer1 = BOARD_WIDTH * BLOCK_SIZE + BLOCK_SIZE;
        int holdYPlayer1 = BLOCK_SIZE;
        int holdBlockSize = BLOCK_SIZE / 2;

        g2d.setColor(Color.WHITE);
        g2d.setFont(new Font("Arial", Font.BOLD, 20));
        g2d.drawString("Hold", 70, holdYPlayer1 + BLOCK_SIZE);  //�hold����蔭

        //畫紅色叉叉
        if(holdBlockedCounterPlayer1 > 0)
            g2d.drawImage(redImage, 70, 120, 120, 170, 0, 0, redImage.getWidth(), redImage.getHeight(), null);
		else if (heldShapePlayer1 != null) {
            int[][] holdMatrix = heldShapePlayer1.getMatrix();
            Color holdColor = heldShapePlayer1.getColor();
			
			for(int i = 0; i < shapeColors.length; i++) {
				if (holdColor == shapeColors[i]) {
					holdMatrix = shapes[i].getMatrix();
					break;
				}
			}

            for (int row = 0; row < holdMatrix.length; row++) {
                for (int col = 0; col < holdMatrix[row].length; col++) {
                    if (holdMatrix[row][col] != 0) {
                        int x = holdXPlayer1 + col * holdBlockSize;
                        int y = holdYPlayer1 + row * holdBlockSize;
						Color endColor = Color.WHITE;
                        g2d.setColor(holdColor);
						GradientPaint gradientPaint = new GradientPaint(x-422, y+90, holdColor, x-422+BLOCK_SIZE, y+90 + BLOCK_SIZE, endColor);
						g2d.setPaint(gradientPaint);
                        g2d.fillRect(x-422, y+90, holdBlockSize, holdBlockSize);//�hold����蔭
                        g2d.setColor(Color.BLACK);
                        g2d.drawRect(x-422, y+90, holdBlockSize, holdBlockSize);//�hold����蔭
                    }
                }
            }
        }

        //畫Reamin
        g2d.setColor(Color.WHITE);
        g2d.setFont(new Font("Arial", Font.BOLD, 20));
        g2d.drawString("Remain  "+holdBlockedCounterPlayer1, 70, holdYPlayer1 + BLOCK_SIZE+150);


        //畫Next
        int nextXPlayer1 = BOARD_WIDTH * BLOCK_SIZE + BLOCK_SIZE;
        int nextYPlayer1 = BLOCK_SIZE;
        int nextBlockSize = BLOCK_SIZE / 2;

        g2d.setColor(Color.WHITE);
        g2d.setFont(new Font("Arial", Font.BOLD, 20));
        g2d.drawString("Next", 725, nextYPlayer1 + BLOCK_SIZE);  
        
        if (shapesPlayer1 != null) {
            //畫圓形
            int indexCircle = 7;
            Shape circleShape = new Shape(shapes[indexCircle].getMatrix(),shapes[indexCircle].getColor());
            int[][] circleMatrix = circleShape.getMatrix();
            Color circleColor = circleShape.getColor();

            for (int row = 0; row < circleMatrix.length; row++) {
                for (int col = 0; col < circleMatrix[row].length; col++) {
                    if (circleMatrix[row][col] != 0) {
                        int x = holdXPlayer1 + col * holdBlockSize;
                        int y = holdYPlayer1 + row * holdBlockSize;
						Color endColor = Color.WHITE;
                        g2d.setColor(circleColor);
						GradientPaint gradientPaint = new GradientPaint(x+209, y+86, circleColor, x+209+BLOCK_SIZE, y+86 + BLOCK_SIZE, endColor);
						g2d.setPaint(gradientPaint);
					
                        g2d.fillRect(x+209, y+86, holdBlockSize, holdBlockSize);//�hold����蔭
                        g2d.setColor(Color.BLACK);
                        g2d.drawRect(x+209, y+86, holdBlockSize, holdBlockSize);//�hold����蔭
                    }
                }
            }

            g2d.setColor(Color.WHITE);
            g2d.setFont(new Font("Arial", Font.BOLD, 20));
            g2d.drawString(" x  "+badshapesPlayer1.size(), 800, nextYPlayer1 + BLOCK_SIZE+70); 

            //畫Next方塊
            for(int order=0,distance=200;order<6;order++)
            {
                int index=(int)shapesPlayer1.get(order);
                Shape nextShape = new Shape(shapes[index].getMatrix(),shapes[index].getColor());
                int[][] nextMatrix = nextShape.getMatrix();
                Color nextColor = nextShape.getColor();

                for (int row = 0; row < nextMatrix.length; row++) {
                    for (int col = 0; col < nextMatrix[row].length; col++) {
                        if (nextMatrix[row][col] != 0) {
                            int x = holdXPlayer1 + col * holdBlockSize;
                            int y = holdYPlayer1 + row * holdBlockSize;
							Color endColor = Color.WHITE;
                            g2d.setColor(nextColor);
							GradientPaint gradientPaint = new GradientPaint(x+210, y+distance, nextColor, x+210+BLOCK_SIZE, y+distance + BLOCK_SIZE, endColor);
							g2d.setPaint(gradientPaint);
							
                            g2d.fillRect(x+210, y+distance, holdBlockSize, holdBlockSize);//�hold����蔭
                            g2d.setColor(Color.BLACK);
                            g2d.drawRect(x+210, y+distance, holdBlockSize, holdBlockSize);//�hold����蔭
                        }
                    }
                }
				
                distance += 80;
            }
        }


        //畫Freq
        g2d.setColor(Color.WHITE);
        g2d.setFont(new Font("Arial", Font.BOLD, 20));
        g2d.drawString("Freq", 70, 350);
        //畫Freq秒數
        g2d.setColor(Color.WHITE);
        g2d.setFont(new Font("Arial", Font.BOLD, 20));
        g2d.drawString(sleepTimePlayer1+" ms", 70, 380);

        //畫技能封鎖
        g2d.setColor(Color.WHITE);
        g2d.setFont(new Font("Arial", Font.BOLD, 20));
        g2d.drawString("Skill Block", 70, 450);
        //畫技能封鎖
        g2d.setColor(Color.WHITE);
        g2d.setFont(new Font("Arial", Font.BOLD, 20));
        g2d.drawString(skillBlockedTimerPlayer1 / 1000 + " s", 70, 480);

        drawGuideLinePlayer1(g2d);
		
        //----------------------------------------------

        // 蝏�摰嗡���
        int boardOffsetXPlayer2 = (BOARD_WIDTH + 4) * BLOCK_SIZE;
        g2d.setColor(Color.GRAY);
        for (int row = 0; row < BOARD_HEIGHT; row++) {
            for (int col = 0; col < BOARD_WIDTH; col++) {
                int x = col * BLOCK_SIZE + boardOffsetXPlayer2;
                int y = row * BLOCK_SIZE;
                g2d.drawRect(x+420, y, BLOCK_SIZE, BLOCK_SIZE);
            }
        }

        for (int row = 0; row < BOARD_HEIGHT; row++) {
            for (int col = 0; col < BOARD_WIDTH; col++) {
                int x = col * BLOCK_SIZE + boardOffsetXPlayer2;
                int y = row * BLOCK_SIZE;
                int value = boardPlayer2[row][col];

                if (value != 0) {
                    Color color = boardColorsPlayer2[row][col];
					Color endColor = Color.WHITE;
                    g2d.setColor(color);
					
					// 设置绘制的渐变颜色
					GradientPaint gradientPaint = new GradientPaint(x+420, y, color, x +420+ BLOCK_SIZE, y + BLOCK_SIZE, endColor);
                    g2d.setPaint(gradientPaint);
					
                    // 绘制纹理图片
                    g2d.drawImage(textureImage, x+420, y, x+420 + BLOCK_SIZE, y + BLOCK_SIZE, 0, 0, textureImage.getWidth(), textureImage.getHeight(), null);

                    // 填充方块
                    g2d.fillRect(x+420, y, BLOCK_SIZE, BLOCK_SIZE);
                    g2d.setColor(Color.BLACK);
                    g2d.drawRect(x+420, y, BLOCK_SIZE, BLOCK_SIZE);
                    
                }
            }
        }

        int[][] shapeMatrixPlayer2 = currentShapePlayer2.getMatrix();
        int shapeXPlayer2 = currentShapePlayer2.getX();
        int shapeYPlayer2 = currentShapePlayer2.getY();

        for (int row = 0; row < shapeMatrixPlayer2.length; row++) {
            for (int col = 0; col < shapeMatrixPlayer2[row].length; col++) {
                if (shapeMatrixPlayer2[row][col] != 0) {
                    int x = (shapeXPlayer2 + col + BOARD_WIDTH + 4) * BLOCK_SIZE;
                    int y = (shapeYPlayer2 + row) * BLOCK_SIZE;
                    Color color = currentShapePlayer2.getColor();
					Color endColor = Color.WHITE;
                    g2d.setColor(color);
					// 设置绘制的渐变颜色
					GradientPaint gradientPaint = new GradientPaint(x+420, y, color, x +420+ BLOCK_SIZE, y + BLOCK_SIZE, endColor);
                    g2d.setPaint(gradientPaint);
					// 绘制纹理图片
                    g2d.drawImage(textureImage, x+420, y, x+420 + BLOCK_SIZE, y + BLOCK_SIZE, 0, 0, textureImage.getWidth(), textureImage.getHeight(), null);

                    g2d.fillRect(x+420, y, BLOCK_SIZE, BLOCK_SIZE);
                    g2d.setColor(Color.BLACK);
                    g2d.drawRect(x+420, y, BLOCK_SIZE, BLOCK_SIZE);
                }
            }
        }

        // 蝏�摰嗡�� hold ����
        int holdXPlayer2 = (BOARD_WIDTH * 2 + 4) * BLOCK_SIZE + BLOCK_SIZE;
        int holdYPlayer2 = BLOCK_SIZE;

        g2d.setColor(Color.WHITE);
        g2d.setFont(new Font("Arial", Font.BOLD, 20));
        g2d.drawString("Hold", 915, holdYPlayer2 + BLOCK_SIZE);

        //畫紅色叉叉
        if(holdBlockedCounterPlayer2 > 0)
            g2d.drawImage(redImage, 915, 120, 980, 170, 0, 0, redImage.getWidth(), redImage.getHeight(), null);
		else if (heldShapePlayer2 != null) {
            int[][] holdMatrix = heldShapePlayer2.getMatrix();
            Color holdColor = heldShapePlayer2.getColor();
			
			for(int i = 0; i < shapeColors.length; i++) {
				if (holdColor == shapeColors[i]) {
					holdMatrix = shapes[i].getMatrix();
					break;
				}
			}

            for (int row = 0; row < holdMatrix.length; row++) {
                for (int col = 0; col < holdMatrix[row].length; col++) {
                    if (holdMatrix[row][col] != 0) {
                        int x = holdXPlayer2 + col * holdBlockSize;
                        int y = holdYPlayer2 + row * holdBlockSize;
						Color endColor = Color.WHITE;
                        g2d.setColor(holdColor);
						// 设置绘制的渐变颜色
						GradientPaint gradientPaint = new GradientPaint(x-192, y+80, holdColor, x -192+ BLOCK_SIZE, y+80 + BLOCK_SIZE, endColor);
						g2d.setPaint(gradientPaint);
                        g2d.fillRect(x-192, y+80, holdBlockSize, holdBlockSize);
                        g2d.setColor(Color.BLACK);
                        g2d.drawRect(x-192, y+80, holdBlockSize, holdBlockSize);
                    }
                }
            }
        }

        //畫Reamin
        g2d.setColor(Color.WHITE);
        g2d.setFont(new Font("Arial", Font.BOLD, 20));
        g2d.drawString("Remain  "+holdBlockedCounterPlayer2, 915, holdYPlayer1 + BLOCK_SIZE+150);

        //畫Next
        int nextXPlayer2 = (BOARD_WIDTH * 2 + 4) * BLOCK_SIZE + BLOCK_SIZE;
        int nextYPlayer2 = BLOCK_SIZE;

        g2d.setColor(Color.WHITE);
        g2d.setFont(new Font("Arial", Font.BOLD, 20));
        g2d.drawString("Next", 1567, nextYPlayer2 + BLOCK_SIZE);

        if (shapesPlayer2 != null) {
            //畫圓形
            int indexCircle = 7;
            Shape circleShape = new Shape(shapes[indexCircle].getMatrix(),shapes[indexCircle].getColor());
            int[][] circleMatrix = circleShape.getMatrix();
            Color circleColor = circleShape.getColor();

            for (int row = 0; row < circleMatrix.length; row++) {
                for (int col = 0; col < circleMatrix[row].length; col++) {
                    if (circleMatrix[row][col] != 0) {
                        int x = holdXPlayer1 + col * holdBlockSize;
                        int y = holdYPlayer1 + row * holdBlockSize;
						Color endColor = Color.WHITE;
                        g2d.setColor(circleColor);
						// 设置绘制的渐变颜色  //圓形:y軸60
						GradientPaint gradientPaint = new GradientPaint(x+1050, y+86, circleColor, x +1050+ BLOCK_SIZE, y+86 + BLOCK_SIZE, endColor);
						g2d.setPaint(gradientPaint);
                        g2d.fillRect(x+1050, y+86, holdBlockSize, holdBlockSize);//�hold����蔭
                        g2d.setColor(Color.BLACK);
                        g2d.drawRect(x+1050, y+86, holdBlockSize, holdBlockSize);//�hold����蔭
                    }
                }
            }

            g2d.setColor(Color.WHITE);
            g2d.setFont(new Font("Arial", Font.BOLD, 20));
            g2d.drawString(" x  "+badshapesPlayer2.size(), 1650, nextYPlayer1 + BLOCK_SIZE+70); 
            
            for(int order=0,distance=200;order<6;order++)
            {
                int index=(int)shapesPlayer2.get(order);
                Shape nextShape = new Shape(shapes[index].getMatrix(),shapes[index].getColor());
                int[][] nextMatrix = nextShape.getMatrix();
                Color nextColor = nextShape.getColor();

                for (int row = 0; row < nextMatrix.length; row++) {
                    for (int col = 0; col < nextMatrix[row].length; col++) {
                        if (nextMatrix[row][col] != 0) {
                            int x = holdXPlayer1 + col * holdBlockSize;
                            int y = holdYPlayer1 + row * holdBlockSize;
							Color endColor = Color.WHITE;
                            g2d.setColor(nextColor);
							// 设置绘制的渐变颜色
							GradientPaint gradientPaint = new GradientPaint(x+1049, y+distance, nextColor, x +1049+ BLOCK_SIZE, y+distance + BLOCK_SIZE, endColor);
							g2d.setPaint(gradientPaint);
                            g2d.fillRect(x+1049, y+distance, holdBlockSize, holdBlockSize);//�hold����蔭
                            g2d.setColor(Color.BLACK);
                            g2d.drawRect(x+1049, y+distance, holdBlockSize, holdBlockSize);//�hold����蔭
                        }
                    }
                }
				
                distance += 80;
            }
        }

        //畫Freq
        g2d.setColor(Color.WHITE);
        g2d.setFont(new Font("Arial", Font.BOLD, 20));
        g2d.drawString("Freq", 915, 350);
        //畫Freq秒數
        g2d.setColor(Color.WHITE);
        g2d.setFont(new Font("Arial", Font.BOLD, 20));
        g2d.drawString(sleepTimePlayer2+" ms", 915, 380);


        //畫技能封鎖
        g2d.setColor(Color.WHITE);
        g2d.setFont(new Font("Arial", Font.BOLD, 20));
        g2d.drawString("Skill Block", 915, 450);
        //畫技能封鎖
        g2d.setColor(Color.WHITE);
        g2d.setFont(new Font("Arial", Font.BOLD, 20));
        g2d.drawString(skillBlockedTimerPlayer2 / 1000 + " s", 915, 480);
		
        drawGuideLinePlayer2(g2d);
		

        // 蝏���瑪
        g2d.setColor(Color.WHITE);
        g2d.fillRect((BOARD_WIDTH + 3) * BLOCK_SIZE+275, 0, 2, BOARD_HEIGHT * BLOCK_SIZE);
    }

    private class TetrisKeyListener implements KeyListener {
        private boolean spacePressedPlayer1;
        private boolean qPressedPlayer1;
        private boolean spacePressedPlayer2;
        private boolean qPressedPlayer2;
		
		private boolean leftPressedPlayer1;
        private boolean rightPressedPlayer1;
        private boolean downPressedPlayer1;
        private boolean leftPressedPlayer2;
        private boolean rightPressedPlayer2;
        private boolean downPressedPlayer2;

        public TetrisKeyListener() {
            spacePressedPlayer1 = false;
            qPressedPlayer1 = false;
            spacePressedPlayer2 = false;
            qPressedPlayer2 = false;
			
            leftPressedPlayer1 = false;
            rightPressedPlayer1 = false;
            downPressedPlayer1 = false;
            leftPressedPlayer2 = false;
            rightPressedPlayer2 = false;
            downPressedPlayer2 = false;
        }

        @Override
        public void keyPressed(KeyEvent e) {
            int keyCode = e.getKeyCode();

            switch (keyCode) {
                // �摰嗡��������
                case KeyEvent.VK_J:
                    if (canMoveLeftPlayer1()) {
						leftPressedPlayer1 = true;
                    }
                    break;
                case KeyEvent.VK_L:
                    if (canMoveRightPlayer1()) {					
						rightPressedPlayer1 = true;
                    }
                    break;
                case KeyEvent.VK_K:
                    if (canMoveDownPlayer1()) {				
						downPressedPlayer1 = true;
                    }
                    break;
                case KeyEvent.VK_I:
                    rotateShapePlayer1();
                    break;
                case KeyEvent.VK_SPACE:
                    spacePressedPlayer1 = true;
                    break;
                case KeyEvent.VK_Q:
                    if (holdBlockedCounterPlayer1 == 0 && !qPressedPlayer1) {
                        holdShapePlayer1();
                        qPressedPlayer1 = true;
                    }
                    break;

                // �摰嗡�������
                case KeyEvent.VK_NUMPAD4:
                    if (canMoveLeftPlayer2()) {
						leftPressedPlayer2 = true;
                    }
                    break;
                case KeyEvent.VK_NUMPAD6:
                    if (canMoveRightPlayer2()) {
						rightPressedPlayer2 = true;
                    }
                    break;
                case KeyEvent.VK_NUMPAD5:
                    if (canMoveDownPlayer2()) {
						downPressedPlayer2 = true;
                    }
                    break;
                case KeyEvent.VK_NUMPAD8:
                    rotateShapePlayer2();
                    break;
                case KeyEvent.VK_DOWN:
                    spacePressedPlayer2 = true;
                    break;
                case KeyEvent.VK_DELETE:
                    if (holdBlockedCounterPlayer2 == 0 && !qPressedPlayer2) {
                        holdShapePlayer2();
                        qPressedPlayer2 = true;
                    }
                    break;
            }

            repaint();
        }

        @Override
        public void keyTyped(KeyEvent e) {
        }

        @Override
        public void keyReleased(KeyEvent e) {
            int keyCode = e.getKeyCode();

            if (keyCode == KeyEvent.VK_SPACE) {
                if (spacePressedPlayer1) {
                    while (canMoveDownPlayer1()) {
                        currentShapePlayer1.moveDown();
                    }
                    placeShapePlayer1();
                    removeFullLinesPlayer1();
                    currentShapePlayer1 = getRandomShape(shapesPlayer1, shapesAdjPlayer1, badshapesPlayer1);

                    if (!isValidPositionPlayer1(currentShapePlayer1)) {
                        resetGamePlayer1();
                    }
                    spacePressedPlayer1 = false;
                }
            } else if (keyCode == KeyEvent.VK_Q) {
                qPressedPlayer1 = false;
            } else if (keyCode == KeyEvent.VK_DOWN) {
                if (spacePressedPlayer2) {
                    while (canMoveDownPlayer2()) {
                        currentShapePlayer2.moveDown();
                    }
                    placeShapePlayer2();
                    removeFullLinesPlayer2();
                    currentShapePlayer2 = getRandomShape(shapesPlayer2, shapesAdjPlayer2, badshapesPlayer2);

                    if (!isValidPositionPlayer2(currentShapePlayer2)) {
                        resetGamePlayer2();
                    }
                    spacePressedPlayer2 = false;
                }
            } else if (keyCode == KeyEvent.VK_DELETE) {
                qPressedPlayer2 = false;
            } else if (keyCode == KeyEvent.VK_J) {
                leftPressedPlayer1 = false;
            } else if (keyCode == KeyEvent.VK_L) {
                rightPressedPlayer1 = false;
            } else if (keyCode == KeyEvent.VK_K) {
                downPressedPlayer1 = false;
            } else if (keyCode == KeyEvent.VK_NUMPAD4) {
                leftPressedPlayer2 = false;
            } else if (keyCode == KeyEvent.VK_NUMPAD6) {
                rightPressedPlayer2 = false;
            } else if (keyCode == KeyEvent.VK_NUMPAD5) {
                downPressedPlayer2 = false;
            }
			
        }

        public boolean isLeftPressedPlayer1() {
            return leftPressedPlayer1;
        }

        public boolean isRightPressedPlayer1() {
            return rightPressedPlayer1;
        }

        public boolean isDownPressedPlayer1() {
            return downPressedPlayer1;
        }
		
		public boolean isLeftPressedPlayer2() {
            return leftPressedPlayer2;
        }

        public boolean isRightPressedPlayer2() {
            return rightPressedPlayer2;
        }

        public boolean isDownPressedPlayer2() {
            return downPressedPlayer2;
        }
    }
	
	public void playerMove() {
		if (keyListener.isLeftPressedPlayer1() && canMoveLeftPlayer1()) {
			currentShapePlayer1.moveLeft();
		}
		
		if (keyListener.isRightPressedPlayer1() && canMoveRightPlayer1()) {					
			currentShapePlayer1.moveRight();
		}
		
		if (keyListener.isDownPressedPlayer1() && canMoveDownPlayer1()) {				
			currentShapePlayer1.moveDown();
		}
		
		if (keyListener.isLeftPressedPlayer2() && canMoveLeftPlayer2()) {
			currentShapePlayer2.moveLeft();
		}
		
		if (keyListener.isRightPressedPlayer2() && canMoveRightPlayer2()) {					
			currentShapePlayer2.moveRight();
		}
		
		if (keyListener.isDownPressedPlayer2() && canMoveDownPlayer2()) {				
			currentShapePlayer2.moveDown();
		}
	}

    private void updatePlayer1() {
        if (canMoveDownPlayer1()) {
            currentShapePlayer1.moveDown();
        } else {
            placeShapePlayer1();
            removeFullLinesPlayer1();
            currentShapePlayer1 = getRandomShape(shapesPlayer1, shapesAdjPlayer1, badshapesPlayer1);

            if (!isValidPositionPlayer1(currentShapePlayer1)) {
                resetGamePlayer1();
            }
        }
    }
	
	private void updatePlayer2() {
        if (canMoveDownPlayer2()) {
            currentShapePlayer2.moveDown();
        } else {
            placeShapePlayer2();
            removeFullLinesPlayer2();
            currentShapePlayer2 = getRandomShape(shapesPlayer2, shapesAdjPlayer2, badshapesPlayer2);

            if (!isValidPositionPlayer2(currentShapePlayer2)) {
                resetGamePlayer2();
            }
        }
    }

    private void resetGamePlayer1() {
		showResetConfirmationDialog("player1");
    }

    private void resetGamePlayer2() {
		showResetConfirmationDialog("player2");
    }
	
	private void resetGame() {
		for (int i = 0; i < BOARD_HEIGHT; i++) {
			for (int j = 0; j < BOARD_WIDTH; j++) {
				boardPlayer1[i][j] = 0;
				boardColorsPlayer1[i][j] = Color.BLACK;
				
				boardPlayer2[i][j] = 0;
				boardColorsPlayer2[i][j] = Color.BLACK;
			}
		}
		
		sleepTimePlayer1 = 400;
		sleepTimePlayer2 = 400;
		
		whiteTimerPlayer1 = 0;
		whiteTimerPlayer2 = 0;
		firstWhitePlayer1 = 0;
		firstWhitePlayer2 = 0;
		
		holdBlockedCounterPlayer1 = 0;
		holdBlockedCounterPlayer2 = 0;
		
		skillBlockedTimerPlayer1 = 0;
		skillBlockedTimerPlayer2 = 0;
		
		
		gamePause = false;
		
		shapesPlayer1 = new ArrayList<>(Arrays.asList(0, 1, 2, 3, 4, 5, 6));
		shapesPlayer2 = new ArrayList<>(Arrays.asList(0, 1, 2, 3, 4, 5, 6));
		shapesAdjPlayer1 = new ArrayList<>(Arrays.asList(0, 1, 2, 3, 4, 5, 6));
		shapesAdjPlayer2 = new ArrayList<>(Arrays.asList(0, 1, 2, 3, 4, 5, 6));
		badshapesPlayer1 = new ArrayList<>(Arrays.asList());
		badshapesPlayer2 = new ArrayList<>(Arrays.asList());
		Collections.shuffle(shapesPlayer1);
		Collections.shuffle(shapesPlayer2);
		Collections.shuffle(shapesAdjPlayer1);
		Collections.shuffle(shapesAdjPlayer2);

        currentShapePlayer1 = getRandomShape(shapesPlayer1, shapesAdjPlayer1, badshapesPlayer1);
        currentShapePlayer2 = getRandomShape(shapesPlayer2, shapesAdjPlayer2, badshapesPlayer2);
		heldShapePlayer1 = null;
		heldShapePlayer2 = null;
		
    }
	
	private void showResetConfirmationDialog(String loser) {
		gamePause = true;
		
		for (int i = 0; i < BOARD_HEIGHT; i++) {
			for (int j = 0; j < BOARD_WIDTH; j++) {
				if (loser == "player1")
				{
					if (boardPlayer1[i][j] == 1)
						boardColorsPlayer1[i][j] = Color.GRAY;
				}
				else
				{
					if (boardPlayer2[i][j] == 1)
						boardColorsPlayer2[i][j] = Color.GRAY;
				}
			}
		}
		repaint();
		
        final JDialog dialog = new JDialog(frame, "重置遊戲", true);
		
		String hint = (loser == "player1")? "玩家二" : "玩家一";
		hint += "勝利，是否重置遊戲？";

        String message = hint + "<br><br>&emsp;&emsp;選擇 是 : 重置遊戲<br>&emsp;&emsp;選擇 否 : 關閉遊戲";
		JLabel messageLabel = new JLabel("<html>" + message + "</html>");
		messageLabel.setHorizontalAlignment(JLabel.CENTER); // 設置水平對齊為中心對齊
		
        JButton yesButton = new JButton("是");
        JButton noButton = new JButton("否");

		JPanel buttonPanel = new JPanel();
		buttonPanel.setLayout(new GridLayout(1, 2, 10, 0)); // 設置網格布局，一行兩列，間距為10像素
		buttonPanel.setBorder(BorderFactory.createEmptyBorder(10, 5, 0, 0)); // 設置邊界空白
		buttonPanel.add(yesButton); // 將是按鈕添加到左側
		buttonPanel.add(noButton); // 將否按鈕添加到右側

		JPanel contentPane = new JPanel();

		contentPane.setLayout(new BorderLayout(10, 10)); // 設置間距為10像素
		contentPane.setBorder(BorderFactory.createEmptyBorder(10, 10, 20, 20)); // 設置邊界空白
		contentPane.add(messageLabel, BorderLayout.NORTH); // 將標籤放在上方
		contentPane.add(buttonPanel, BorderLayout.CENTER); // 將按鈕面板放在中間

		dialog.setContentPane(contentPane); // 設定對話框的內容面板

        yesButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                dialog.dispose();
				gamePause = false;
				resetGame();
				repaint();
				revalidate();
            }
        });
		

        noButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                dialog.dispose();
                frame.dispose();
				System.exit(0);
            }
        });
		
		dialog.setDefaultCloseOperation(JDialog.DO_NOTHING_ON_CLOSE);
		dialog.addWindowListener(new WindowAdapter() {
			public void windowClosing(WindowEvent e) {
                dialog.dispose();
                frame.dispose();
				System.exit(0);
			}
		});
		
		dialog.setFocusable(true);
		dialog.addKeyListener(new KeyAdapter() {
			public void keyPressed(KeyEvent e) {
				if (e.getKeyCode() == KeyEvent.VK_SPACE) {
					e.consume();
				}
			}
		});


        dialog.setSize(275, 180);
        dialog.setLocationRelativeTo(frame);
        dialog.setVisible(true);
    }

    private void holdShapePlayer1() {
		Color currentColor = currentShapePlayer1.getColor();
		if (currentColor == shapeColors[7])
			return;
		
        if (heldShapePlayer1 == null) {
            heldShapePlayer1 = currentShapePlayer1;
            currentShapePlayer1 = getRandomShape(shapesPlayer1, shapesAdjPlayer1, badshapesPlayer1);
        } else {
            Shape temp = currentShapePlayer1;
            currentShapePlayer1 = heldShapePlayer1;
            heldShapePlayer1 = temp;
        }
        currentShapePlayer1.setX(BOARD_WIDTH / 2 - currentShapePlayer1.getMatrix()[0].length / 2);
        currentShapePlayer1.setY(0);
    }

    private void holdShapePlayer2() {
		Color currentColor = currentShapePlayer2.getColor();
		if (currentColor == shapeColors[7])
			return;
		
        if (heldShapePlayer2 == null) {
            heldShapePlayer2 = currentShapePlayer2;
            currentShapePlayer2 = getRandomShape(shapesPlayer2, shapesAdjPlayer2, badshapesPlayer2);
        } else {
            Shape temp = currentShapePlayer2;
            currentShapePlayer2 = heldShapePlayer2;
            heldShapePlayer2 = temp;
        }
        currentShapePlayer2.setX(BOARD_WIDTH / 2 - currentShapePlayer2.getMatrix()[0].length / 2);
        currentShapePlayer2.setY(0);
    }

    public static void main(String[] args) {
        TetrisGame game = new TetrisGame();
        frame.add(game);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setExtendedState(JFrame.MAXIMIZED_BOTH);
        frame.pack();
        frame.setLocationRelativeTo(null);
        frame.setVisible(true);
		
        int dropTimerPlayer1 = 0;
        int dropTimerPlayer2 = 0;
        int playerMoveTimer = 0;

        while (true) {
        	dropTimerPlayer1 += 1;
        	dropTimerPlayer2 += 1;
			playerMoveTimer += 1;
			
			if (skillBlockedTimerPlayer1 > 0) skillBlockedTimerPlayer1--;
			if (skillBlockedTimerPlayer2 > 0) skillBlockedTimerPlayer2--;
			
			if(playerMoveTimer == 50){
				game.playerMove();
				playerMoveTimer = 0;
			}
        	
            if (dropTimerPlayer1 * 2 >= sleepTimePlayer1) {
                game.updatePlayer1();
                dropTimerPlayer1 = 0;
                if (sleepTimePlayer1 > 275) sleepTimePlayer1 -= 1;
            }
			if (dropTimerPlayer2 * 2 >= sleepTimePlayer2) {
                game.updatePlayer2();
                dropTimerPlayer2 = 0;
                if (sleepTimePlayer2 > 275) sleepTimePlayer2 -= 1;
            }
            
            if (game.firstWhitePlayer1 > 0)
            	if (game.whiteTimerPlayer1 == 50) {
            		game.whiteTimerPlayer1 = 0;
            	}else {
            		game.whiteTimerPlayer1 += 1;
            	}
            
             if (game.firstWhitePlayer2 > 0)
            	if (game.whiteTimerPlayer2 == 50) {
            		game.whiteTimerPlayer2 = 0;
            	}else {
            		game.whiteTimerPlayer2 += 1;
            	}
				
			game.removeFullLinesPlayer1();
			game.removeFullLinesPlayer2();
            
            game.repaint();

            try {
				Thread.sleep(1);
            }
			catch (InterruptedException e) {
                e.printStackTrace();
            }
			
			try {
				if (gamePause) {
					while (gamePause) Thread.sleep(0);
					dropTimerPlayer1 = 0;
					dropTimerPlayer2 = 0;
					playerMoveTimer = 0;
				}
			}
			catch (InterruptedException e) {
				e.printStackTrace();
			}
        }
    }
}
