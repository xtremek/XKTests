<?php

class NewUser extends TPage
{
    public function checkUsername($sender, $param)
    {
        $param->IsValid = UserRecord::finder()->findByPk($this->Username->Text) === null;
    }

    public function createButtonClicked($sender, $param) 
    {
        if ($this->IsValid) {
            $userRecord = new UserRecord;
            $userRecord->username = $this->Username->Text;
            $userRecord->password = $this->Password->Text;
            $userRecord->email = $this->Email->Text;
            $userRecord->role = (int)$this->Role->SelectedValue;
            $userRecord->first_name = $this->FirstName->Text;
            $userRecord->last_name = $this->LastName->Text;

            $userRecord->save();

            $this->Response->redirect($this->Service->DefaultPageUrl);
        }
    }
}

?>