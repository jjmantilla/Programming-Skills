
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class Principal_I extends Canvas implements AdjustmentListener, TextListener, ActionListener, MouseListener {

    public JFrame pantalla;
    public TextField texto;
    public JLabel pa, me, descr;
    public JPanel panel;
    public JComboBox lista;
    private Scrollbar barra;
    public String envio = "", tipo = "Unipolar";
    public boolean ar = true, a = true;

    public Principal_I() {
        pantalla = new JFrame("                 ****** Metodos de Representacion Binaria ******");
        pantalla.setLayout(new BorderLayout());
        pantalla.setBounds(200, 30, 700, 600);
        pantalla.getContentPane().setBackground(Color.WHITE);
        panel = new JPanel();
        panel.setBackground(Color.WHITE);
        panel.setBounds(0, 0, 200, 200);
        panel.setLayout(new FlowLayout());
        pantalla.add(panel, BorderLayout.SOUTH);
        pantalla.add(this, BorderLayout.CENTER);
        pantalla.setResizable(false);

        pa = new JLabel("Ingrese la Palabra: ");
        pa.setBounds(300, 150, 200, 20);
        pa.setVisible(true);
        panel.add(pa);
        texto = new TextField(20);
        texto.setBounds(200, 200, 200, 20);
        panel.add(texto);
        me = new JLabel("Metodo de Graficacion: ");
        panel.add(me);
        lista = new JComboBox();
        lista.addItem("Unipolar");
        lista.addItem("AMI");
        lista.addItem("MLT-3");
        lista.addItem("Polar_RZ");
        lista.addItem("Polar_NRZ-L");
        lista.addItem("Polar_NRZ-I");
        lista.addItem("Manchester");
        lista.addItem("Manchester_Dif");
        lista.addItem("PSeudoternaria");
        lista.addActionListener(this);
        panel.add(lista);

        descr = new JLabel("Descripción del Metodo");
        descr.addMouseListener(this);
        descr.setCursor(new Cursor(12));
        panel.add(descr);

        barra = new Scrollbar(0, 1, 1, 1, 1);
        barra.addAdjustmentListener(this);
        pantalla.add(barra, BorderLayout.NORTH);
        validate();
        texto.addTextListener(this);

        pantalla.show();
        pantalla.setDefaultCloseOperation(pantalla.EXIT_ON_CLOSE);
    }

    public void paint(Graphics g) {
        int val;
        int ab = 20, abc = 10, x = 0, yy = 0, yyy = 0;
        int[] abAcum = new int[5];
        int[] arriba = new int[5];
        int prev = 0;
        int aux_bip = 266;
        g.setColor(Color.BLACK);
        g.fillRect(100, 50, 500, 400);
        for (int y = 0; y < 5; y++) {
            abAcum[y] = 180;
            arriba[y] = 180;
        }
        g.setColor(Color.yellow);
        g.drawLine(170, 250, 600, 250);
        g.drawLine(180, 50, 180, 450);
        g.drawString("1", 155, 170);
        g.drawString("0", 155, 255);
        g.drawString("-1", 155, 340);
        g.setColor(Color.WHITE);
        for (int i = 100; i < 288; i += 170) {
            for (int j = 170; j <= 722; j += 11) {
                g.drawLine(j, i + 65, j + 1, i + 65);
            }
        }

        for (int u = 0; u < (envio.length() < 31 ? envio.length() : 30); u++) {
            g.setColor(Color.WHITE);
            for (int q = 70; q <= 374; q += 12) {
                g.drawLine(abAcum[0] + ab, q, abAcum[0] + ab, q + 1);
            }
            g.setColor(Color.GREEN);
            g.drawString("" + envio.charAt(u), abAcum[0] + 6, 80);
            val = (int) (envio.charAt(u)) - 48;
            if (val == 1) {
                abAcum[0] += ab;
            } else {
                abAcum[0] += ab;
            }
            prev = val;
        }
        for (int i = 0; i < envio.length(); i++) {
            if (tipo.equalsIgnoreCase("Unipolar")) {
                if ((int) (envio.charAt(i)) - 48 == 1) {
                    g.drawLine(arriba[0], 161, (arriba[0] += ab), 161);
                } else {
                    if ((i > 0) && ((int) (envio.charAt(i - 1)) - 48) == 1) {
                        g.drawLine(arriba[0], 250, arriba[0], 161);
                    }
                    g.drawLine(arriba[0], 250, (arriba[0] += ab), 250);//abajo
                    if ((i < envio.length() - 1) && ((int) (envio.charAt(i + 1)) - 48) == 1) {
                        g.drawLine(arriba[0], 250, arriba[0], 161);
                    }
                }
            }
            if (tipo.equalsIgnoreCase("Polar_NRZ-L")) {
                if ((int) (envio.charAt(i)) - 48 == 0) {
                    g.drawLine(arriba[0], 213, (arriba[0] += ab), 213);
                } else {
                    if (i > 0 && ((int) (envio.charAt(i - 1)) - 48) == 0) {
                        g.drawLine(arriba[0], 298, arriba[0], 213);
                    }
                    g.drawLine(arriba[0], 298, (arriba[0] += ab), 298);
                    if ((i < envio.length() - 1) && ((int) (envio.charAt(i + 1)) - 48) == 0) {
                        g.drawLine(arriba[0], 298, arriba[0], 213);
                    }
                }
            }
            if (tipo.equalsIgnoreCase("Polar_NRZ-I")) {
                if ((int) (envio.charAt(i)) - 48 == 1) {
                    for (int j = 0; j < 1; j++) {
                        if (ar) {
                            g.drawLine(arriba[0], 298, (arriba[0] += ab), 298);
                            if ((i < envio.length() - 1) && ((int) (envio.charAt(i + 1)) - 48) == 1) {
                                g.drawLine(arriba[0], 298, arriba[0], 213);
                            }
                            x = 298;
                            ar = false;
                            break;
                        }
                        if (ar == false) {
                            g.drawLine(arriba[0], 213, (arriba[0] += ab), 213);
                            if ((i < envio.length() - 1) && ((int) (envio.charAt(i + 1)) - 48) == 1) {
                                g.drawLine(arriba[0], 298, arriba[0], 213);
                            }
                            x = 213;
                            ar = true;
                            break;
                        }
                    }
                } else {
                    g.drawLine(arriba[0], x, (arriba[0] += ab), x);
                    if ((i < envio.length() - 1) && ((int) (envio.charAt(i + 1)) - 48) == 1) {
                        g.drawLine(arriba[0], x, arriba[0], 213);
                    }
                }
            }
            if (tipo.equalsIgnoreCase("Polar_RZ")) {
                if ((int) (envio.charAt(i)) - 48 == 0) {
                    if (i > 0 && ((int) (envio.charAt(i - 1)) - 48) == 1) {
                        g.drawLine(arriba[0], 298, arriba[0], 250);
                    }
                    g.drawLine(arriba[0], 298, (arriba[0] += abc), 298);
                    g.drawLine(arriba[0], 298, arriba[0], 250);
                    g.drawLine(arriba[0], 250, (arriba[0] += abc), 250);
                    if ((i < envio.length() - 1) && ((int) (envio.charAt(i + 1)) - 48) == 0) {
                        g.drawLine(arriba[0], 298, arriba[0], 250);
                    }
                } else {
                    if (i > 0 && ((int) (envio.charAt(i - 1)) - 48) == 0) {
                        g.drawLine(arriba[0], 250, arriba[0], 213);
                    }
                    g.drawLine(arriba[0], 213, (arriba[0] += abc), 213);
                    g.drawLine(arriba[0], 250, arriba[0], 213);
                    g.drawLine(arriba[0], 250, (arriba[0] += abc), 250);
                    if ((i < envio.length() - 1) && ((int) (envio.charAt(i + 1)) - 48) == 1) {
                        g.drawLine(arriba[0], 250, arriba[0], 213);
                    }
                }
            }
            if (tipo.equalsIgnoreCase("Manchester")) {
                if ((int) (envio.charAt(i)) - 48 == 0) {
                    g.drawLine(arriba[0], 213, (arriba[0] += abc), 213);
                    g.drawLine(arriba[0], 298, arriba[0], 213);
                    g.drawLine(arriba[0], 298, (arriba[0] += abc), 298);
                    if ((i < envio.length() - 1) && ((int) (envio.charAt(i + 1)) - 48) == 0) {
                        g.drawLine(arriba[0], 298, arriba[0], 213);
                    }

                } else {
                    g.drawLine(arriba[0], 298, (arriba[0] += abc), 298);
                    g.drawLine(arriba[0], 298, arriba[0], 213);
                    g.drawLine(arriba[0], 213, (arriba[0] += abc), 213);
                    if ((i < envio.length() - 1) && ((int) (envio.charAt(i + 1)) - 48) == 1) {
                        g.drawLine(arriba[0], 298, arriba[0], 213);
                    }
                }
            }
            if (tipo.equalsIgnoreCase("Manchester_Dif")) {
                if ((int) (envio.charAt(i)) - 48 == 1) {
                    g.drawLine(arriba[0], 213, (arriba[0] += abc), 213);
                    g.drawLine(arriba[0], 298, (arriba[0] += abc), 298);
                } else {
                }
            }
            if (tipo.equalsIgnoreCase("AMI")) {
                if ((int) (envio.charAt(i)) - 48 == 0) {
                    g.drawLine(arriba[0], 250, (arriba[0] += ab), 250);
                    if ((i < envio.length() - 1) && ((int) (envio.charAt(i + 1)) - 48) == 1 && a) {
                        g.drawLine(arriba[0], 250, arriba[0], 168);
                    }
                    if ((i < envio.length() - 1) && ((int) (envio.charAt(i + 1)) - 48) == 1 && a == false) {
                        g.drawLine(arriba[0], 338, arriba[0], 250);
                    }
                } else {
                    for (int j = 0; j < 1; j++) {
                        if (a) {
                            g.drawLine(arriba[0], 168, (arriba[0] += ab), 168);
                            if ((i < envio.length() - 1) && ((int) (envio.charAt(i + 1)) - 48) == 1) {
                                g.drawLine(arriba[0], 338, arriba[0], 168);
                            }
                            if ((i < envio.length() - 1) && ((int) (envio.charAt(i + 1)) - 48) == 0) {
                                g.drawLine(arriba[0], 250, arriba[0], 168);
                            }
                            a = false;
                            break;
                        }
                        if (a == false) {
                            g.drawLine(arriba[0], 338, (arriba[0] += ab), 338);
                            if ((i < envio.length() - 1) && ((int) (envio.charAt(i + 1)) - 48) == 1) {
                                g.drawLine(arriba[0], 338, arriba[0], 168);
                            }
                            if ((i < envio.length() - 1) && ((int) (envio.charAt(i + 1)) - 48) == 0) {
                                g.drawLine(arriba[0], 338, arriba[0], 250);
                            }
                            a = true;
                            break;
                        }
                    }
                }
            }
            if (tipo.equalsIgnoreCase("PSeudoternaria")) {
                if ((int) (envio.charAt(i)) - 48 == 1) {
                    g.drawLine(arriba[0], 250, (arriba[0] += ab), 250);
                    if ((i < envio.length() - 1) && ((int) (envio.charAt(i + 1)) - 48) == 0 && a) {
                        g.drawLine(arriba[0], 250, arriba[0], 168);
                    }
                    if ((i < envio.length() - 1) && ((int) (envio.charAt(i + 1)) - 48) == 0 && a == false) {
                        g.drawLine(arriba[0], 338, arriba[0], 250);
                    }
                } else {
                    for (int j = 0; j < 1; j++) {
                        if (a) {
                            g.drawLine(arriba[0], 168, (arriba[0] += ab), 168);
                            if ((i < envio.length() - 1) && ((int) (envio.charAt(i + 1)) - 48) == 0) {
                                g.drawLine(arriba[0], 338, arriba[0], 168);
                            }
                            if ((i < envio.length() - 1) && ((int) (envio.charAt(i + 1)) - 48) == 1) {
                                g.drawLine(arriba[0], 250, arriba[0], 168);
                            }
                            a = false;
                            break;
                        }
                        if (a == false) {
                            g.drawLine(arriba[0], 338, (arriba[0] += ab), 338);
                            if ((i < envio.length() - 1) && ((int) (envio.charAt(i + 1)) - 48) == 0) {
                                g.drawLine(arriba[0], 338, arriba[0], 168);
                            }
                            if ((i < envio.length() - 1) && ((int) (envio.charAt(i + 1)) - 48) == 1) {
                                g.drawLine(arriba[0], 338, arriba[0], 250);
                            }
                            a = true;
                            break;
                        }
                    }
                }
            }
            if (tipo.equalsIgnoreCase("MLT-3")) {
                if ((int) (envio.charAt(i)) - 48 == 1) {
                    if (a) {
                        g.drawLine(arriba[0], 168, (arriba[0] += ab), 168);
                        x = 168;
                        a = false;
                    }
                    if ((i < envio.length() - 1) && ((int) (envio.charAt(i + 1)) - 48) == 1) {
                        g.drawLine(arriba[0], 250, (arriba[0] += ab), 250);
                        i++;
                        x = 250;
                    }
                    if ((i < envio.length() - 1) && ((int) (envio.charAt(i + 1)) - 48) == 1) {
                        g.drawLine(arriba[0], 338, (arriba[0] += ab), 338);
                        //i++;
                        x = 338;
                    }
                    if ((i < envio.length() - 1) && ((int) (envio.charAt(i + 1)) - 48) == 1) {
                        g.drawLine(arriba[0], 250, (arriba[0] += ab), 250);
                        a = true;
                        i++;
                        x = 250;
                    }
//                    if (ar == false && a == false && (i < envio.length() - 1) && ((int) (envio.charAt(i + 1)) - 48) == 1) {
//                        a = true;
//                        ar = false;
//                        g.drawLine(arriba[0], 250, (arriba[0] += ab), 250);
//                        x= 250;
//                    }
                } else {
                    g.drawLine(arriba[0], x, (arriba[0] += ab), x);
                }
            }
        }
    }

    public static void main(String[] args) {
        JFrame.setDefaultLookAndFeelDecorated(true);
        new Principal_I();
    }

    public void adjustmentValueChanged(AdjustmentEvent e) {
    }

    public void textValueChanged(TextEvent e) {
        String cadena = texto.getText();
        try {
            byte[] bis = cadena.getBytes("ASCII");
            for (int i = 0; i < bis.length; i++) {
                //System.out.println(bis[i] + "   " + Integer.toBinaryString(bis[i]).toString());
                envio += Integer.toBinaryString(bis[i]).toString();
            }
        } catch (Exception ee) {
            ee.printStackTrace();
        }
        //System.out.println(envio);
        if ((texto.getText().length() - 29) > 0) {
            barra.setMaximum(texto.getText().length());
        } else {
            barra.setMaximum(1);
        }
        barra.setValue(-1);
        validate();
        if (texto.getText().equalsIgnoreCase("")) {
            envio = "";
            this.repaint();
        }
        this.repaint();
    }

    public void actionPerformed(ActionEvent e) {
        if (e.getSource() == lista) {
            System.out.println("entro " + lista.getSelectedItem());
            if (lista.getSelectedItem().toString().equalsIgnoreCase("Polar_RZ")) {
                tipo = "Polar_RZ";
            }
            if (lista.getSelectedItem().toString().equalsIgnoreCase("Unipolar")) {
                tipo = "Unipolar";
            }
            if (lista.getSelectedItem().toString().equalsIgnoreCase("Polar_NRZ-L")) {
                tipo = "Polar_NRZ-L";
            }
            if (lista.getSelectedItem().toString().equalsIgnoreCase("Polar_NRZ-I")) {
                tipo = "Polar_NRZ-I";
            }
            if (lista.getSelectedItem().toString().equalsIgnoreCase("Manchester")) {
                tipo = "Manchester";
            }
            if (lista.getSelectedItem().toString().equalsIgnoreCase("Manchester_Dif")) {
                tipo = "Manchester_Dif";
            }
            if (lista.getSelectedItem().toString().equalsIgnoreCase("AMI")) {
                tipo = "AMI";
            }
            if (lista.getSelectedItem().toString().equalsIgnoreCase("PSeudoternaria")) {
                tipo = "PSeudoternaria";
            }
            if (lista.getSelectedItem().toString().equalsIgnoreCase("MLT-3")) {
                tipo = "MLT-3";
            }
        }
        this.repaint();
    }

    public void mouseClicked(MouseEvent e) {
        // throw new UnsupportedOperationException("Not supported yet.");
    }

    public void mousePressed(MouseEvent e) {
        if (e.getSource() == descr) {
            new Principal( tipo );
        }
    }

    public void mouseReleased(MouseEvent e) {
        // throw new UnsupportedOperationException("Not supported yet.");
    }

    public void mouseEntered(MouseEvent e) {
        // throw new UnsupportedOperationException("Not supported yet.");
    }

    public void mouseExited(MouseEvent e) {
        //throw new UnsupportedOperationException("Not supported yet.");
    }
}
