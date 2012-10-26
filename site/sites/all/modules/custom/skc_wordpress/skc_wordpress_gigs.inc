<?php
class GigMigration extends Migration {
  public function __construct() {
    parent::__construct(MigrateGroup::getInstance('gigs'));
    
    $query = db_select('skc_gigs_gig', 'gig');
    $query->join('skc_gigs_performance', 'performance', 'gig.id = performance.gigID');
    $query->join('skc_gigs_venue', 'venue', 'gig.venueID = venue.id');
    $query->fields('gig', array('id','date','notes','eventName'));
    $query->fields('performance', array('time','ages'));
    $query->fields('venue', array('name','link'));
    
    $this->source = new MigrateSourceSQL($query, array(), NULL, array('map_joinable'=>FALSE));
    $this->destination = new MigrateDestinationNode('gig');
    
    $this->map = new MigrateSQLMap($this->machineName,
        array(
          'id' => array('type' => 'int',
                          'unsigned' => TRUE,
                          'not null' => TRUE,
                         )
        ),
        MigrateDestinationNode::getKeySchema()
      );
    
    
    $this->addFieldMapping('title', 'eventName');
    $this->addFieldMapping('body', 'notes');
    $this->addFieldMapping('uid')->defaultValue(165);
    $this->addFieldMapping('field_datetime', 'date');
    $this->addFieldMapping('created', 'date');
    $this->addFieldMapping('field_ages', 'ages');
    $this->addFieldMapping('field_ages:create_term')->defaultValue(TRUE);
    $this->addFieldMapping('field_location', 'name');
    $this->addFieldMapping('field_location:create_term')->defaultValue(TRUE);
    
    $this->addUnmigratedDestinations(array('body:summary','body:format',
      'body:language','status','changed','promote',
      'sticky','revision','log','language','tnid','revision_uid',
      'is_new','field_ages:source_type','field_cost','path',
      'field_location:source_type','comment','pathauto'),
      'Unmigrated Destinations');
    $this->addUnmigratedSources(array('time','link'), t('Unmigrated Sources'));
    
  }
  
  public function prepareRow($row){
    
    if((!isset($row->eventName) || $row->eventName==='')){
      if(isset($row->name) && $row->name!==''){
        $row->eventName = 'At ' . $row->name;
      }else{
        $row->eventName = 'Gig #' . $row->id;
      }
    }
    //$row->date = new DateTime($row->date . ' ' . $row->time);
    //$row->date = drupal_json_encode($row->date . ' ' . $row->time);
    //$row->date = (string) $row->date . ' ' . $row->time;
    $row->date = (string) strtotime($row->date . ' ' . $row->time);
    
    if(isset($row->link) && $row->link!==''){
      $row->notes .= ' ' . $row->link;
    }
    
  }
}
