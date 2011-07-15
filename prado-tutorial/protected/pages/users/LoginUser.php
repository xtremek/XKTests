<?php

class LoginUser extends TPage
{
    public function validateUser($sender, $param)
    {
        $authManager = $this->Application->getModule('auth');
        if (!$authManager->login($this->Username->Text, $this->Password->Text)) {
            $param->IsValid = false;
        }
    }

    public function loginButtonClicked($sender, $param)
    {
        if ($this->Page->IsValid) {
            $url = $this->Application->getModule('auth')->ReturnUrl;

            if (empty($url)) {
                $url = $this->Service->DefaultPageUrl;
            }

            $this->Response->redirect($url);
        }
    }
}

?>