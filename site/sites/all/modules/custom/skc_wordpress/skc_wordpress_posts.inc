<?php
class OldPostMigration extends Migration {
  public function __construct() {
    parent::__construct(MigrateGroup::getInstance('old_posts'));
    
    $query = db_select('skc_posts', 'posts');
    $query->fields('posts', array('ID','post_date_gmt','post_content','post_title'));
    $query->condition('post_date_gmt',2008,'<');
    $query->condition('ID',70,'<');
    $query->condition('post_type','post','=');
    
    $this->source = new MigrateSourceSQL($query, array(), NULL, array('map_joinable'=>FALSE));
    $this->destination = new MigrateDestinationNode('article');
    
    $this->map = new MigrateSQLMap($this->machineName,
        array(
          'ID' => array('type' => 'int',
                          'unsigned' => TRUE,
                          'not null' => TRUE,
                         )
        ),
        MigrateDestinationNode::getKeySchema()
      );
    
    
    $this->addFieldMapping('title', 'post_title');
    $this->addFieldMapping('body', 'post_content');
    $this->addFieldMapping('uid')->defaultValue(165);
    $this->addFieldMapping('created', 'post_date_gmt');
    
    $this->addUnmigratedDestinations(array('body:summary','body:format',
      'body:language','status','changed','promote','field_tags',
      'sticky','revision','log','language','tnid','revision_uid',
      'is_new','field_tags:source_type','field_image','path','field_image:file_class',
      'comment','pathauto','field_tags:create_term','field_image:language',
      'field_image:destination_dir','field_image:destination_file','field_image:file_replace',
      'field_image:preserve_files','field_image:source_dir','field_image:alt',
      'field_image:title'),
      'Unmigrated Destinations');
    $this->addUnmigratedSources(array(), t('Unmigrated Sources'));
    
  }
  
  public function prepareRow($row){
    if(trim($row->post_title)===''){
      $row->post_title = 'no title';
    }
  }
}

