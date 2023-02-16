import GLKit

extension ViewController: GLKViewControllerDelegate {
    func glkViewControllerUpdate(_ controller: GLKViewController) {
        renderer.update();
    }
}

class ViewController: GLKViewController {
    
    private var context: EAGLContext?
    private var renderer: Renderer!
    
    private func setupGL() {
        context = EAGLContext(api: .openGLES3)
        EAGLContext.setCurrent(context)
        if let view = self.view as? GLKView, let context = context {
            view.context = context
            delegate = self as GLKViewControllerDelegate
            renderer = Renderer();
            renderer.setup(view);
            renderer.loadModels();
        }
    }
    
    override func viewDidLoad() {
        super.viewDidLoad();
        setupGL();
        
    }
    
    override func glkView(_ view: GLKView, drawIn rect: CGRect) {
        renderer.draw(rect);
    }
    
    @objc func moveDirection(_ sender: UIButton) {
        // this function should handle making the snake go in the direction specified by one block.
        
    }
    
}
