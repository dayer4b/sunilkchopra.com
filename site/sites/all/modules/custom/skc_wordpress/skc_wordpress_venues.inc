<?php
class VenuesMigration extends Migration {
  public function __construct() {
    parent::__construct(MigrateGroup::getInstance('example'));
    // The example uses a SQL database as source.
    $query = db_select('gtrwordpress2.skc_gigs_venue', 'venue')
             ->fields('venue', array('id','name','address','city','state','country','postalCode','phone','link'));
             
    $this->source = new MigrateSourceSQL($query);
    // We migrate into "page" nodes.
    $this->destination = new MigrateDestinationNode('page');

    // We instantiate the MigrateMap
    $this->map = new MigrateSQLMap($this->machineName,
        array(
          'pgid' => array('type' => 'int',
                          'unsigned' => TRUE,
                          'not null' => TRUE,
                         )
        ),
        MigrateDestinationNode::getKeySchema()
      );

    // Finally we add simple field mappings 
    $this->addFieldMapping('title', 'page_title');
    $this->addFieldMapping('body', 'page_body');
  }
}
