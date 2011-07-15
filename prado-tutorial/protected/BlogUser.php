<?php

Prado::using('System.Security.TDbUserManager');

class BlogUser extends TDbUser
{
    public function createUser($username)
    {
        $userRecord = UserRecord::finder()->findByPk($username);
        if ($userRecord instanceof UserRecord) {
            $user = new BlogUser($this->Manager);
            $user->Name = $username;
            $user->Roles = ($userRecord->role == 1 ? 'admin' : 'user');
            $user->IsGuest = false;

            return $user;
        } else {
            return null;
        }
    }

    public function validateUser($username, $password) 
    {
        return UserRecord::finder()->findBy_username_AND_password($username, $password) != null;
    }


    public function getIsAdmin()
    {
        return $this->isInRole('admin');
    }
}

?>