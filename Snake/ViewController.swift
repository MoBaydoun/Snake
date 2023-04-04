import GLKit

extension ViewController: GLKViewControllerDelegate {
    func glkViewControllerUpdate(_ controller: GLKViewController) {
        bridge.update();
        scoreLabel.text = "Score: " + String(bridge.getScore());
        isGameOver = bridge.getIsGameOver();
    }
}

class ViewController: GLKViewController {
    
    private var context: EAGLContext?
    private var bridge: Bridge!
    private var scoreLabel: UILabel!
    private var gameOverLabel: UILabel!
    private var resetButton: UIButton!
    private var isGameOver: Bool!
    private var timer: Timer?
    
    private func setupGL() {
        context = EAGLContext(api: .openGLES3)
        EAGLContext.setCurrent(context)
        if let view = self.view as? GLKView, let context = context {
            view.context = context
            delegate = self as GLKViewControllerDelegate
            bridge = Bridge();
            bridge.setup(view);
            bridge.loadModels();
        }
    }
    
    override func viewDidLoad() {
        super.viewDidLoad();
        setupGL();

        timer = Timer();
        timer = Timer.scheduledTimer(withTimeInterval: 1, repeats: true, block: { _ in
            self.gameOver();
        })

        let swipeR = UISwipeGestureRecognizer(target: self, action: #selector(self.moveDirection(_:)))
        swipeR.direction = .right;
        view.addGestureRecognizer(swipeR);
        
        let swipeU = UISwipeGestureRecognizer(target: self, action: #selector(self.moveDirection(_:)))
        swipeU.direction = .up;
        view.addGestureRecognizer(swipeU);
        
        let swipeL = UISwipeGestureRecognizer(target: self, action: #selector(self.moveDirection(_:)))
        swipeL.direction = .left;
        view.addGestureRecognizer(swipeL);
        
        let swipeD = UISwipeGestureRecognizer(target: self, action: #selector(self.moveDirection(_:)))
        swipeD.direction = .down;
        view.addGestureRecognizer(swipeD);
        
        scoreLabel = UILabel(frame: CGRect(x: 0, y: 80, width: 90, height: 20))
        scoreLabel.center.x = view.center.x;
        scoreLabel.textColor = .white;
        scoreLabel.numberOfLines = 0;
        view.addSubview(scoreLabel);
        
        gameOverLabel = UILabel(frame: CGRect(x: 0, y: 100, width: 90, height: 20))
        gameOverLabel.center.x = view.center.x;
        gameOverLabel.textColor = .white;
        gameOverLabel.numberOfLines = 0;
        gameOverLabel.isHidden = true;
        view.addSubview(gameOverLabel);
        
        resetButton = UIButton(frame: CGRect(x: 200, y: 200, width: 100, height: 40));
        resetButton.addTarget(self, action: #selector(self.resetGame(_:)), for: .touchUpInside);
        resetButton.setTitle("Play Again", for: .normal);
        resetButton.isHidden = true;
        view.addSubview(resetButton); 
    }
    
    override func glkView(_ view: GLKView, drawIn rect: CGRect) {
        bridge.draw(rect);
    }
    
    @objc func moveDirection(_ sender: UISwipeGestureRecognizer) {
        // this function should handle making the snake go in the direction specified by one block.
        
        switch(sender.direction) {
            case .right:
                bridge.setDir(0)
            case .up:
                bridge.setDir(3)
            case .left:
                bridge.setDir(2)
            case .down:
                bridge.setDir(1)
            default:
                return
        }
    }

    private func gameOver() {
        if (isGameOver) {
            gameOverLabel.isHidden = false;
            resetButton.isHidden = false;
        }
    }
    
    @objc func resetGame(_ sender: UIButton) {
        bridge.resetGame();
        gameOverLabel.isHidden = true;
        resetButton.isHidden = true;
    }
}
