<?php

class ListPost extends TPage
{
	public function onInit($param)
	{
		parent::onInit($param);
		if (!$this->IsPostBack) {
			$this->Repeater->VirtualItemCount = PostRecord::finder()->count();
			$this->populateData();
		}
	}

	public function pageChanged($sender, $param)
	{
		$this->Repeater->CurrentPageIndex = $param->NewPageIndex;
		$this->populateData();
	}

	protected function populateData()
	{
		$offset = $this->Repeater->CurrentPageIndex * $this->Repeater->PageSize;
		$limit = $this->Repeater->PageSize;

		if ($offset + $limit > $this->Repeater->VirtualItemCount) {
			$limit = $this->Repeater->VirtualItemCount - $offset;
		}

		$this->Repeater->DataSource = $this->getPosts($offset, $limit);
		$this->Repeater->dataBind();
	}

	protected function getPosts($offset, $limit)
	{
		$criteria = new TActiveRecordCriteria;
		$criteria->OrdersBy['create_time'] = 'desc';
		$criteria->Limit = $limit;
		$criteria->Offset = $offset;
		
		return PostRecord::finder()->withAuthor()->findAll($criteria);
	}
}

?>