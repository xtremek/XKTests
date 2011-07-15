<?php

class EditUser extends TPage
{
    public function onInit($param) 
    {
        parent::onInit($param);

        if ($this->IsPostBack) {
            $userRecord = $this->UserRecord;

            $this->Username->Text = $userRecord->username;
            $this->Email->Text = $userRecord->email;
            $this->Role->SelectValue = $userRecord->role;
            $this->FirstName->Text = $userRecord->first_name;
            $this->LastName->Text = $userRecord->last_name;
        }
    }

    public function saveButtonClicked($sender, $param) 
    {
        if ($this->IsValid) {
            $userRecord = $this->UserRecord;
          
            $userRecord->username = $this->Username->Text;
            if (!empty($this->Password->Text)) {
                $userRecord->password = $this->Password->Text;
            }
            $userRecord->email = $this->Email->Text;
            if ($this->User->IsAdmin) {
                $userRecord->role = (int)$this->Role->SelectedValue;
            }
            $userRecord->first_name = $this->FirstName->Text;
            $userRecord->last_name = $this->LastName->text;

            $userRecord->save();

            $this->Response->redirect($this->Service->DefaultPageUrl);
        }
    }

    public function getUserRecord()
    {
        $username = $this->User->Name;

        if ($this->User->IsAdmin && $this->Request['username'] !== null) {
            $username = $this->Request['username'];
        }

        $userRecord = UserRecord::finder()->findByPk($username);
        if (!($userRecord instanceof UserRecord)) {
            throw new THttpException(500, 'Username is invalid');
        }

        return $userRecord;
    }
}

?>