<?php

class Contact extends TPage
{
    public function submitButtonClicked($sender, $param)
    {
        if ($this->IsValid) {
            $name = $this->Name->Text;
            $email = $this->Email->Text;
            $feedback = $this->Feedback->Text;

            $this->mailFeedback($name, $email, $feedback);
        }
    }

    public function mailFeedback($name, $email, $feedback)
    {
        // Do something?
    }
}

?>