import GLKit

extension ViewController: GLKViewControllerDelegate {
    func glkViewControllerUpdate(_ controller: GLKViewController) {
        bridge.update();
    }
}

class ViewController: GLKViewController {
    
    private var context: EAGLContext?
    private var bridge: Bridge!
    
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
    
}
