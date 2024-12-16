#ifndef OUTPUTVIEWER_H
#define OUTPUTVIEWER_H


#include <QPushButton>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QListWidget>
#include <QFileInfo>

class OutputViewer : public QDialog {
    Q_OBJECT

public:
    /**
     * @brief Constructor of the OutputViewer class.
     *
     */
    explicit OutputViewer(const QString &outputDir, const QStringList &allowedExtensions, QWidget *parent = nullptr);

    /**
     * @brief Destructor of the OutputViewer class.
     */
    ~OutputViewer() override = default;

private:
    /**
     * @brief Directory with output files
     */
    QString outputDirectory;

    /**
     * @brief Allowed file extensions
     */
    QStringList extensions;

    /**
     * @brief List view for files in the directory
     */
    QListWidget *fileListView;

    /**
     * @brief Button to open the file
     */
    QPushButton *openButton;

    /**
     * @brief Button to open the file in a browser
     */
    QPushButton *browseButton;

    /**
     * @brief Layout for the widgets
     */
    QVBoxLayout *layout;

    /**
     * @brief Set up the user interface
     */
    void setupUI();

    /**
     * @brief Connect signals and slots
     */
    void createEvents();

    /**
     * @brief Update the list of files in the directory
     */
    void updateFileList();

signals:
private slots:

    /**
     * @brief Open the selected file
     */
    void openFile();

    /**
     * @brief Open the selected file in a browser
     */
    void browseFile();
};

#endif // OUTPUTVIEWER_H
