/*Ý tưởng

- Mỗi thao tác là một Command

- Command có Execute() và Undo()

- Editor quản lý:

  + UndoStack

  + RedoStack
*/

#include <iostream>
#include <stack>
#include <memory>

// ===============================
// 1️⃣ Receiver: ImageViewport
// ===============================

class ImageViewport {
private:
    double scale = 1.0;
    double rotation_angle = 0.0;

public:
    void Zoom(double factor) {
        scale *= factor;
        std::cout << "Zoom: scale = " << scale << "\n";
    }

    void SetScale(double newScale) {
        scale = newScale;
        std::cout << "Set scale = " << scale << "\n";
    }

    double GetScale() const {
        return scale;
    }

    void Rotate(double angle) {
        rotation_angle += angle;
        std::cout << "Rotate: angle = " << rotation_angle << "\n";
    }

    void SetRotation(double angle) {
        rotation_angle = angle;
        std::cout << "Set rotation = " << rotation_angle << "\n";
    }

    double GetRotation() const {
        return rotation_angle;
    }
};

// ===============================
// 2️⃣ Command Interface
// ===============================

class Command {
public:
    virtual ~Command() = default;
    virtual void Execute() = 0;
    virtual void Undo() = 0;
};

// ===============================
// 3️⃣ Concrete Command: Zoom
// ===============================

class ZoomCommand : public Command {
private:
    ImageViewport& viewport;
    double factor;
    double previous_scale;  // Lưu trạng thái trước

public:
    ZoomCommand(ImageViewport& vp, double f)
        : viewport(vp), factor(f) {}

    void Execute() override {
        previous_scale = viewport.GetScale();
        viewport.Zoom(factor);
    }

    void Undo() override {
        viewport.SetScale(previous_scale);
    }
};

// ===============================
// 4️⃣ Concrete Command: Rotate
// ===============================

class RotateCommand : public Command {
private:
    ImageViewport& viewport;
    double angle;
    double previous_angle;

public:
    RotateCommand(ImageViewport& vp, double a)
        : viewport(vp), angle(a) {}

    void Execute() override {
        previous_angle = viewport.GetRotation();
        viewport.Rotate(angle);
    }

    void Undo() override {
        viewport.SetRotation(previous_angle);
    }
};

// ===============================
// 5️⃣ Invoker: Editor
// ===============================

class Editor {
private:
    std::stack<std::shared_ptr<Command>> UndoStack;
    std::stack<std::shared_ptr<Command>> RedoStack;

public:
    void ExecuteCommand(std::shared_ptr<Command> cmd) {
        cmd->Execute();
        UndoStack.push(cmd);

        // Khi có thao tác mới -> clear Redo
        while (!RedoStack.empty()) {
            RedoStack.pop();
        }
    }

    void Undo() {
        if (UndoStack.empty()) return;

        auto cmd = UndoStack.top();
        UndoStack.pop();

        cmd->Undo();
        RedoStack.push(cmd);
    }

    void Redo() {
        if (RedoStack.empty()) return;

        auto cmd = RedoStack.top();
        RedoStack.pop();

        cmd->Execute();
        UndoStack.push(cmd);
    }
};

// ===============================
// 6️⃣ Client
// ===============================

int main() {
    ImageViewport viewport;
    Editor editor;

    auto ZoomCmd = std::make_shared<ZoomCommand>(viewport, 1.5);
    auto RotateCmd = std::make_shared<RotateCommand>(viewport, 90);

    editor.ExecuteCommand(ZoomCmd);
    editor.ExecuteCommand(RotateCmd);

    std::cout << "\nUndo:\n";
    editor.Undo();
    editor.Undo();

    std::cout << "\nRedo:\n";
    editor.Redo();
    editor.Redo();

    return 0;
}