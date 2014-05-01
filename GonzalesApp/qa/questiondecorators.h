#ifndef QUESTIONDECORATORS_H
#define QUESTIONDECORATORS_H

class QuestionDecorator
{
public:
    virtual void decorate() = 0;
    virtual void clear() = 0;
};

class TextQuestionDecorator: public QuestionDecorator
{
public:
    virtual void setDecorator(std::shared_ptr<TextQuestionDecorator> p_decorator)
    {
        m_decorator = p_decorator;
    }

private:
    std::shared_ptr<TextQuestionDecorator> m_decorator;
};

class TextStringDecorator: public TextQuestionDecorator
{
    TextStringDecorator(const QString &p_question, std::shared_ptr<TextQuestionPresentation> p_presentation):
        m_question(p_question),
        m_presentation(p_presentation)
    {}

public:
    void decorate()
    {
        m_presentation->setText(m_question);
        m_decorator->decorate();
    }

    void clear()
    {
        m_presentation->clear();
    }

    using TextQuestionDecorator::setDecorator;

private:
    std::string m_question;
    std::shared_ptr<TextQuestionPresentation> m_presentation;
};


class CanvasQuestionDecorator: public QuestionDecorator
{
public:
    virtual void setDecorator(std::shared_ptr<CanvasQuestionDecorator> p_decorator)
    {
        m_decorator = p_decorator;
    }

private:
    std::shared_ptr<CanvasQuestionDecorator> m_decorator;
};

class BackgroundDecorator: public CanvasQuestionDecorator
{
    StringDecorator(const QString &p_question, std::shared_ptr<TextQuestionPresentation> p_presentation):
        m_question(p_question),
        m_presentation(p_presentation)
    {}

public:
    void decorate()
    {
        m_presentation->setText(m_question);
    }

    void clear()
    {
        m_presentation->clear();
    }

private:
    std::string m_question;
    std::shared_ptr<TextQuestionPresentation> m_presentation;

};

class StringDecorator: public QuestionDecorator
{
    StringDecorator(const QString &p_question, std::shared_ptr<TextQuestionPresentation> p_presentation):
        m_question(p_question),
        m_presentation(p_presentation)
    {}

public:
    void decorate()
    {
        m_presentation->setText(m_question);
    }

    void clear()
    {
        m_presentation->clear();
    }

private:
    std::string m_question;
    std::shared_ptr<TextQuestionPresentation> m_presentation;

};


#endif // QUESTIONDECORATORS_H
