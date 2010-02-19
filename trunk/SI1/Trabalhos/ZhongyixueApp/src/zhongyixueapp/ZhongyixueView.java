/*
 * ZhongyixueView.java
 */

package zhongyixueapp;

import java.awt.BorderLayout;
import org.jdesktop.application.Action;
import org.jdesktop.application.ResourceMap;
import org.jdesktop.application.SingleFrameApplication;
import org.jdesktop.application.FrameView;
import org.jdesktop.application.TaskMonitor;
import java.awt.Dimension;
import java.awt.Frame;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;
import javax.swing.BoxLayout;
import javax.swing.Timer;
import javax.swing.Icon;
import javax.swing.JDialog;
import javax.swing.JFrame;
import javax.swing.ImageIcon ;
import javax.swing.JButton;
import javax.swing.JComponent;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTable;


/**
 * The application's main frame.
 */
public class ZhongyixueView extends FrameView {

    public ZhongyixueView(SingleFrameApplication app, ZhongyixueDB db) {
        super(app);
        this.db = db ;
        initComponents();

        // customizing app icon
        java.net.URL imgURL = getClass().getResource(("resources/Zhongyixue.png"));
        this.getFrame().setIconImage(new ImageIcon(imgURL).getImage());

        // status bar initialization - message timeout, idle icon and busy animation, etc
        ResourceMap resourceMap = getResourceMap();
        int messageTimeout = resourceMap.getInteger("StatusBar.messageTimeout");
        messageTimer = new Timer(messageTimeout, new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                statusMessageLabel.setText("");
            }
        });
        messageTimer.setRepeats(false);
        int busyAnimationRate = resourceMap.getInteger("StatusBar.busyAnimationRate");
        for (int i = 0; i < busyIcons.length; i++) {
            busyIcons[i] = resourceMap.getIcon("StatusBar.busyIcons[" + i + "]");
        }
        busyIconTimer = new Timer(busyAnimationRate, new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                busyIconIndex = (busyIconIndex + 1) % busyIcons.length;
                statusAnimationLabel.setIcon(busyIcons[busyIconIndex]);
            }
        });
        idleIcon = resourceMap.getIcon("StatusBar.idleIcon");
        statusAnimationLabel.setIcon(idleIcon);
        progressBar.setVisible(false);
        populateTabbedPane(tabbedPane) ;
        // connecting action tasks to status bar via TaskMonitor
        TaskMonitor taskMonitor = new TaskMonitor(getApplication().getContext());
        taskMonitor.addPropertyChangeListener(new java.beans.PropertyChangeListener() {
            public void propertyChange(java.beans.PropertyChangeEvent evt) {
                String propertyName = evt.getPropertyName();
                if ("started".equals(propertyName)) {
                    if (!busyIconTimer.isRunning()) {
                        statusAnimationLabel.setIcon(busyIcons[0]);
                        busyIconIndex = 0;
                        busyIconTimer.start();
                    }
                    progressBar.setVisible(true);
                    progressBar.setIndeterminate(true);
                } else if ("done".equals(propertyName)) {
                    busyIconTimer.stop();
                    statusAnimationLabel.setIcon(idleIcon);
                    progressBar.setVisible(false);
                    progressBar.setValue(0);
                } else if ("message".equals(propertyName)) {
                    String text = (String)(evt.getNewValue());
                    statusMessageLabel.setText((text == null) ? "" : text);
                    messageTimer.restart();
                } else if ("progress".equals(propertyName)) {
                    int value = (Integer)(evt.getNewValue());
                    progressBar.setVisible(true);
                    progressBar.setIndeterminate(false);
                    progressBar.setValue(value);
                }
            }

        });



    }
    
    private void populateTabbedPane(javax.swing.JTabbedPane p) {        
        createPanelPatient() ;
        createPanelDoctor() ;
        createPanelSchedule() ;
        createPanelTreatment() ;
    }

    private void createPanelPatient() {
        java.net.URL patientIconURL = getClass().getResource(("resources/patient.gif"));
        ImageIcon patientIcon = new ImageIcon(patientIconURL) ;
        JComponent panelPatient = new JPanel() ;
        tabbedPane.addTab("Pacientes", patientIcon, panelPatient,
                          "Painel de Pacientes");
        tabbedPane.setMnemonicAt(0, KeyEvent.VK_1);
        panelPatient.setLayout(new BorderLayout(5,5)) ;

        queryPatient = new ZhongyixueTableModel(db) ;
        tablePatient = new JTable(queryPatient) ;
        JScrollPane panePatient = new JScrollPane(tablePatient,
                JScrollPane.VERTICAL_SCROLLBAR_ALWAYS, JScrollPane.HORIZONTAL_SCROLLBAR_ALWAYS);
        
        panelPatient.setEnabled(true);
        //panePatient.setVisible(true) ;
        JPanel panelPatientButtons = new JPanel() ;
        
        JButton buttonListPatients = new JButton();
        buttonListPatients.setIcon(new ImageIcon(getClass().getResource(("resources/find.png"))) ) ;

        JButton buttonDiagnosticCard = new JButton();
        buttonDiagnosticCard.setIcon(new ImageIcon(getClass().getResource(("resources/patient2.gif"))) ) ;

        JButton buttonSchedulePatient = new JButton();
        buttonSchedulePatient.setIcon(new ImageIcon(getClass().getResource(("resources/schedule.gif"))) ) ;

        JButton buttonAddPatient = new JButton();
        buttonAddPatient.setIcon(new ImageIcon(getClass().getResource(("resources/addPatient.png")))) ;

        JButton buttonRemovePatient = new JButton();
        buttonRemovePatient.setIcon(new ImageIcon(getClass().getResource(("resources/removePatient.png")))) ;

        buttonListPatients.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                try {
                    queryPatient.setQuery("SELECT Nome, BI, NIF, Morada, Telefone," +
                            " Idade, \"Data Nascimento\", Profissao, \"Estado Civil\"," +
                            "\"Decl. Responsabilidade\", Email, \"Data Registo\" " +
                            "FROM LISTA_PACIENTES");                    
                }catch (Exception ex) {
                    JOptionPane.showMessageDialog(new Frame(), "Erro na procura de pacientes",
                        "Erro", JOptionPane.ERROR_MESSAGE);
                }
            }
        });

        buttonAddPatient.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                try {
                    db.insertPatient();
                    JOptionPane.showMessageDialog(new Frame(), "Inserção bem sucedida",
                        "Informação", JOptionPane.INFORMATION_MESSAGE);
                }catch (Exception ex) {
                    ex.printStackTrace() ;
                    JOptionPane.showMessageDialog(new Frame(), "Erro na inserção de paciente",
                        "Erro", JOptionPane.ERROR_MESSAGE);
                }
            }
        });

        buttonRemovePatient.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                try {
                    int linePatient = tablePatient.getSelectedRow() ;
                    if (linePatient < 0)
                        JOptionPane.showMessageDialog(new Frame(), "Seleccione um paciente a eliminar",
                        "Erro", JOptionPane.ERROR_MESSAGE);
                    else
                        db.removePatient((String) tablePatient.getValueAt(linePatient, 1));
                }catch (Exception ex) {
                    ex.printStackTrace() ;
                    JOptionPane.showMessageDialog(new Frame(), "Erro na eliminação do paciente",
                        "Erro", JOptionPane.ERROR_MESSAGE);
                }
            }
        });

        buttonSchedulePatient.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                try {
                    int linePatient = tablePatient.getSelectedRow() ;
                    int lineDoctor = tableDoctor.getSelectedRow() ;
                    if ((linePatient < 0) || (lineDoctor < 0))
                        JOptionPane.showMessageDialog(new Frame(), "Seleccione um paciente e um terapeuta",
                        "Erro", JOptionPane.ERROR_MESSAGE);
                    else {
                        db.insertSchedule((String) tablePatient.getValueAt(linePatient, 1),
                                        (String) tableDoctor.getValueAt(lineDoctor, 1));
                        JOptionPane.showMessageDialog(new Frame(), "Inserção bem sucedida",
                        "Informação", JOptionPane.INFORMATION_MESSAGE);
                    }
                }catch (Exception ex) {
                    ex.printStackTrace() ;
                    JOptionPane.showMessageDialog(new Frame(), "Erro no agendamento de consulta",
                        "Erro", JOptionPane.ERROR_MESSAGE);
                }
            }
        });

        buttonDiagnosticCard.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                try {
                    queryPatient.setQuery("SELECT \"Nome Paciente\", \"BI Paciente\"," +
                            "\"NIF Paciente\", Morada, Telefone, Idade,\"Data Nascimento\"," +
                            " Profissao, \"Estado Civil\", \"Decl. Responsabilidade\"," +
                            " Email, \"Data Registo\", \"Nome Sintoma\", \"Desc. Sintoma\"," +
                            " \"Data Sintoma\", Notas, \"Nome Padrao\", \"Desc. Padrao\", \"Nome Terapeuta\" " +
                            "FROM DIAGNOSTICO_PACIENTES");
                }catch (Exception ex) {
                    ex.printStackTrace() ;
                    JOptionPane.showMessageDialog(new Frame(), "Erro na ficha de diagnostico",
                        "Erro", JOptionPane.ERROR_MESSAGE);
                }
            }
        });

        panelPatientButtons.setLayout(new BoxLayout(panelPatientButtons, BoxLayout.PAGE_AXIS)) ;
        panelPatient.add(panelPatientButtons, BorderLayout.LINE_END) ;
        panelPatient.add(panePatient, BorderLayout.CENTER);

        panelPatientButtons.add(buttonListPatients) ;
        panelPatientButtons.add(buttonDiagnosticCard) ;
        panelPatientButtons.add(buttonSchedulePatient);
        panelPatientButtons.add(buttonAddPatient) ;
        panelPatientButtons.add(buttonRemovePatient) ;
    }


    private void createPanelDoctor() {
        java.net.URL doctorIconURL = getClass().getResource(("resources/doctor.gif"));
        ImageIcon doctorIcon = new ImageIcon(doctorIconURL) ;
        JComponent panelDoctor = new JPanel();
        tabbedPane.addTab("Terapeutas", doctorIcon, panelDoctor,
                          "Painel de Terapeutas");
        tabbedPane.setMnemonicAt(1, KeyEvent.VK_2);

        panelDoctor.setLayout(new BorderLayout(5,5)) ;

        queryDoctor = new ZhongyixueTableModel(db) ;
        tableDoctor = new JTable(queryDoctor) ;
        JScrollPane paneDoctor = new JScrollPane(tableDoctor,
                JScrollPane.VERTICAL_SCROLLBAR_ALWAYS, JScrollPane.HORIZONTAL_SCROLLBAR_ALWAYS);

        panelDoctor.setEnabled(true);
        JPanel panelDoctorButtons = new JPanel() ;

        JButton buttonListDoctors = new JButton();
        buttonListDoctors.setIcon(new ImageIcon(getClass().getResource(("resources/find.png"))) ) ;

        JButton buttonAddDoctor = new JButton();
        buttonAddDoctor.setIcon(new ImageIcon(getClass().getResource(("resources/addPatient.png")))) ;

        JButton buttonRemoveDoctor = new JButton();
        buttonRemoveDoctor.setIcon(new ImageIcon(getClass().getResource(("resources/removePatient.png")))) ;

        JButton buttonRetireDoctor = new JButton();
        buttonRetireDoctor.setIcon(new ImageIcon(getClass().getResource(("resources/retire.png")))) ;

        buttonListDoctors.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                try {
                    queryDoctor.setQuery("SELECT Nome, BI, NIF, Morada, Telefone," +
                            " Idade, \"Data Nascimento\", \"Data Conclusao\"," +
                            "\"Em Funcoes\" " +
                            "FROM LISTA_TERAPEUTAS");
                }catch (Exception ex) {
                    ex.printStackTrace() ;
                    JOptionPane.showMessageDialog(new Frame(), "Erro na procura de Terapeuta",
                        "Erro", JOptionPane.ERROR_MESSAGE);
                }
            }
        });

        buttonAddDoctor.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                try {
                    db.insertDoctor();
                    JOptionPane.showMessageDialog(new Frame(), "Inserção bem sucedida",
                        "Informação", JOptionPane.INFORMATION_MESSAGE);
                }catch (Exception ex) {
                    ex.printStackTrace() ;
                    JOptionPane.showMessageDialog(new Frame(), "Erro na inserção de Terapeuta",
                        "Erro", JOptionPane.ERROR_MESSAGE);
                }
            }
        });

        buttonRemoveDoctor.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                JOptionPane.showMessageDialog(new Frame(), "Função não implementada",
                        "Aviso", JOptionPane.WARNING_MESSAGE);
            }
        });

        buttonRetireDoctor.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                try {
                    int lineDoctor = tableDoctor.getSelectedRow() ;
                    if (lineDoctor < 0)
                        JOptionPane.showMessageDialog(new Frame(), "Seleccione um terapeuta a suspender",
                        "Erro", JOptionPane.ERROR_MESSAGE);
                    else {
                        db.retireDoctor((String) tableDoctor.getValueAt(lineDoctor, 1));
                        JOptionPane.showMessageDialog(new Frame(), "Terapeuta suspenso",
                        "Informação", JOptionPane.INFORMATION_MESSAGE);
                    }
                }catch (Exception ex) {
                    ex.printStackTrace() ;
                    JOptionPane.showMessageDialog(new Frame(), "Erro na suspensão de funções",
                        "Erro", JOptionPane.ERROR_MESSAGE);
                }
            }
        });

        panelDoctorButtons.setLayout(new BoxLayout(panelDoctorButtons, BoxLayout.PAGE_AXIS)) ;
        panelDoctor.add(panelDoctorButtons, BorderLayout.LINE_END) ;
        panelDoctor.add(paneDoctor, BorderLayout.CENTER);
        panelDoctorButtons.add(buttonListDoctors) ;
        panelDoctorButtons.add(buttonRetireDoctor) ;
        panelDoctorButtons.add(buttonAddDoctor) ;
        panelDoctorButtons.add(buttonRemoveDoctor) ;
        
    }

    private void createPanelSchedule() {
        java.net.URL scheduleIconURL = getClass().getResource(("resources/schedule.gif"));
        ImageIcon scheduleIcon = new ImageIcon(scheduleIconURL) ;
        JComponent panelSchedule = new JPanel();
        tabbedPane.addTab("Consultas", scheduleIcon, panelSchedule,
                          "Painel de Consultas");
        tabbedPane.setMnemonicAt(2, KeyEvent.VK_3);

        panelSchedule.setLayout(new BorderLayout(5,5)) ;

        querySchedule = new ZhongyixueTableModel(db) ;
        tableSchedule = new JTable(querySchedule) ;
        JScrollPane paneSchedule = new JScrollPane(tableSchedule,
                JScrollPane.VERTICAL_SCROLLBAR_ALWAYS, JScrollPane.HORIZONTAL_SCROLLBAR_ALWAYS);

        panelSchedule.setEnabled(true);
        //panePatient.setVisible(true) ;
        JPanel panelScheduleButtons = new JPanel() ;

        JButton buttonListSchedule = new JButton();
        buttonListSchedule.setIcon(new ImageIcon(getClass().getResource(("resources/find.png"))) ) ;

        buttonListSchedule.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                try {
                    querySchedule.setQuery("SELECT \"BI Paciente\", \"Nome Paciente\", "+
                            "\"BI Terapeuta\", \"Nome Terapeuta\",\"Num Consulta\","+
                            "\"Data Consulta\", \"Relatorio\" " +
                            "FROM LISTA_CONSULTAS");
                }catch (Exception ex) {
                    ex.printStackTrace() ;
                    JOptionPane.showMessageDialog(new Frame(), "Erro na procura de Consulta",
                        "Erro", JOptionPane.ERROR_MESSAGE);
                }
            }
        });

        panelScheduleButtons.setLayout(new BoxLayout(panelScheduleButtons, BoxLayout.PAGE_AXIS)) ;
        panelSchedule.add(panelScheduleButtons, BorderLayout.LINE_END) ;
        panelSchedule.add(paneSchedule, BorderLayout.CENTER);
        panelScheduleButtons.add(buttonListSchedule) ;
    }

    private void createPanelTreatment() {
        java.net.URL treatmentIconURL = getClass().getResource(("resources/treatment.gif"));
        ImageIcon treatmentIcon = new ImageIcon(treatmentIconURL) ;
        JComponent panelTreatment = new JPanel() ;
        panelTreatment.setPreferredSize(new Dimension(410, 50));
        tabbedPane.addTab("Tratamentos", treatmentIcon, panelTreatment,
                              "Painel de Tratamentos");
        tabbedPane.setMnemonicAt(3, KeyEvent.VK_4);
        panelTreatment.setLayout(new BorderLayout(5,5)) ;

        queryTreatment = new ZhongyixueTableModel(db) ;
        tableTreatment = new JTable(queryTreatment) ;
        JScrollPane paneTreatment = new JScrollPane(tableTreatment,
                JScrollPane.VERTICAL_SCROLLBAR_ALWAYS, JScrollPane.HORIZONTAL_SCROLLBAR_ALWAYS);

        panelTreatment.setEnabled(true);
        JPanel panelTreatmentButtons = new JPanel() ;

        JButton buttonListTreatment = new JButton();
        buttonListTreatment.setIcon(new ImageIcon(getClass().getResource(("resources/find.png"))) ) ;

        buttonListTreatment.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                try {
                    queryTreatment.setQuery("SELECT nome, bi, nif, morada, telefone," +
                            " idade, dataNasc, dataConclusao, emFuncoes " +
                            "FROM LISTA_TRATAMENTOS");
                }catch (Exception ex) {
                    ex.printStackTrace() ;
                    JOptionPane.showMessageDialog(new Frame(), "Erro na procura de Tratamento",
                        "Erro", JOptionPane.ERROR_MESSAGE);
                }
            }
        });

        panelTreatmentButtons.setLayout(new BoxLayout(panelTreatmentButtons, BoxLayout.PAGE_AXIS)) ;
        panelTreatment.add(panelTreatmentButtons, BorderLayout.LINE_END) ;
        panelTreatment.add(paneTreatment, BorderLayout.CENTER);
        panelTreatmentButtons.add(buttonListTreatment) ;
    }

    @Action
    public void showAboutBox() {
        if (aboutBox == null) {
            JFrame mainFrame = ZhongyixueApp.getApplication().getMainFrame();
            aboutBox = new ZhongyixueAboutBox(mainFrame);
            aboutBox.setLocationRelativeTo(mainFrame);
        }
        ZhongyixueApp.getApplication().show(aboutBox);
    }

    /** This method is called from within the constructor to
     * initialize the form.
     * WARNING: Do NOT modify this code. The content of this method is
     * always regenerated by the Form Editor.
     */
    @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        mainPanel = new javax.swing.JPanel();
        tabbedPane = new javax.swing.JTabbedPane();
        menuBar = new javax.swing.JMenuBar();
        javax.swing.JMenu fileMenu = new javax.swing.JMenu();
        javax.swing.JMenuItem exitMenuItem = new javax.swing.JMenuItem();
        javax.swing.JMenu helpMenu = new javax.swing.JMenu();
        javax.swing.JMenuItem aboutMenuItem = new javax.swing.JMenuItem();
        statusPanel = new javax.swing.JPanel();
        javax.swing.JSeparator statusPanelSeparator = new javax.swing.JSeparator();
        statusMessageLabel = new javax.swing.JLabel();
        statusAnimationLabel = new javax.swing.JLabel();
        progressBar = new javax.swing.JProgressBar();

        mainPanel.setName("mainPanel"); // NOI18N

        tabbedPane.setTabLayoutPolicy(javax.swing.JTabbedPane.SCROLL_TAB_LAYOUT);
        tabbedPane.setTabPlacement(javax.swing.JTabbedPane.LEFT);
        org.jdesktop.application.ResourceMap resourceMap = org.jdesktop.application.Application.getInstance(zhongyixueapp.ZhongyixueApp.class).getContext().getResourceMap(ZhongyixueView.class);
        tabbedPane.setFont(resourceMap.getFont("tabbedPane.font")); // NOI18N
        tabbedPane.setName("tabbedPane"); // NOI18N

        javax.swing.GroupLayout mainPanelLayout = new javax.swing.GroupLayout(mainPanel);
        mainPanel.setLayout(mainPanelLayout);
        mainPanelLayout.setHorizontalGroup(
            mainPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addComponent(tabbedPane, javax.swing.GroupLayout.DEFAULT_SIZE, 618, Short.MAX_VALUE)
        );
        mainPanelLayout.setVerticalGroup(
            mainPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addComponent(tabbedPane, javax.swing.GroupLayout.DEFAULT_SIZE, 453, Short.MAX_VALUE)
        );

        menuBar.setName("menuBar"); // NOI18N

        fileMenu.setText(resourceMap.getString("fileMenu.text")); // NOI18N
        fileMenu.setName("fileMenu"); // NOI18N

        javax.swing.ActionMap actionMap = org.jdesktop.application.Application.getInstance(zhongyixueapp.ZhongyixueApp.class).getContext().getActionMap(ZhongyixueView.class, this);
        exitMenuItem.setAction(actionMap.get("quit")); // NOI18N
        exitMenuItem.setName("exitMenuItem"); // NOI18N
        fileMenu.add(exitMenuItem);

        menuBar.add(fileMenu);

        helpMenu.setText(resourceMap.getString("helpMenu.text")); // NOI18N
        helpMenu.setName("helpMenu"); // NOI18N

        aboutMenuItem.setAction(actionMap.get("showAboutBox")); // NOI18N
        aboutMenuItem.setName("aboutMenuItem"); // NOI18N
        helpMenu.add(aboutMenuItem);

        menuBar.add(helpMenu);

        statusPanel.setName("statusPanel"); // NOI18N

        statusPanelSeparator.setName("statusPanelSeparator"); // NOI18N

        statusMessageLabel.setName("statusMessageLabel"); // NOI18N

        statusAnimationLabel.setHorizontalAlignment(javax.swing.SwingConstants.LEFT);
        statusAnimationLabel.setName("statusAnimationLabel"); // NOI18N

        progressBar.setName("progressBar"); // NOI18N

        javax.swing.GroupLayout statusPanelLayout = new javax.swing.GroupLayout(statusPanel);
        statusPanel.setLayout(statusPanelLayout);
        statusPanelLayout.setHorizontalGroup(
            statusPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addComponent(statusPanelSeparator, javax.swing.GroupLayout.DEFAULT_SIZE, 618, Short.MAX_VALUE)
            .addGroup(statusPanelLayout.createSequentialGroup()
                .addContainerGap()
                .addComponent(statusMessageLabel)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, 448, Short.MAX_VALUE)
                .addComponent(progressBar, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(statusAnimationLabel)
                .addContainerGap())
        );
        statusPanelLayout.setVerticalGroup(
            statusPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(statusPanelLayout.createSequentialGroup()
                .addComponent(statusPanelSeparator, javax.swing.GroupLayout.PREFERRED_SIZE, 2, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                .addGroup(statusPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(statusMessageLabel)
                    .addComponent(statusAnimationLabel)
                    .addComponent(progressBar, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addGap(3, 3, 3))
        );

        setComponent(mainPanel);
        setMenuBar(menuBar);
        setStatusBar(statusPanel);
    }// </editor-fold>//GEN-END:initComponents

    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JPanel mainPanel;
    private javax.swing.JMenuBar menuBar;
    private javax.swing.JProgressBar progressBar;
    private javax.swing.JLabel statusAnimationLabel;
    private javax.swing.JLabel statusMessageLabel;
    private javax.swing.JPanel statusPanel;
    private javax.swing.JTabbedPane tabbedPane;
    // End of variables declaration//GEN-END:variables

    private final Timer messageTimer;
    private final Timer busyIconTimer;
    private final Icon idleIcon;
    private final Icon[] busyIcons = new Icon[15];
    private int busyIconIndex = 0;

    private JDialog aboutBox;
    private JTable tablePatient;
    private JTable tableDoctor;
    private JTable tableSchedule;
    private JTable tableTreatment;

    private ZhongyixueDB db ;
    private ZhongyixueTableModel queryPatient ;
    private ZhongyixueTableModel queryDoctor ;
    private ZhongyixueTableModel querySchedule ;
    private ZhongyixueTableModel queryTreatment ;
}
