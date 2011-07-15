<?php

class AdminUser extends TPage
{
    public function onInit($param)
    {
        parent::onInit($param);

        $this->UserGrid->DataSource = UserRecord::finder()->findAll();
        $this->UserGrid->dataBind();
    }

    public function deleteButtonClicked($sender, $param)
    {
        $item = $param->Item;
        $username = $this->UserGrid->DataKeys($item->ItemIndex);
        UserRecord::finder()->deleteByPk($username);
    }
}

?>