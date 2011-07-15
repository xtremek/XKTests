class CreateBankAccounts < ActiveRecord::Migration
  def self.up
    create_table :bank_accounts do |t|

      t.timestamps
    end
  end

  def self.down
    drop_table :bank_accounts
  end
end
